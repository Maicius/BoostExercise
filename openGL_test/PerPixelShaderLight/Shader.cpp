#include "Shader.h"
Shader::Shader(GLchar* vertexPath, GLchar* fragmentPath)
{
	this->Program = glCreateProgram();

	if(this->Program ==0) {
		fprintf(stderr, "Error to create shader program");
		exit(2);
	}
	GLchar *fs;
	fs = readFile(fragmentPath);
	GLchar *vs;
	vs = readFile(vertexPath);
    AddShader(this->Program, vs, GL_VERTEX_SHADER);
    AddShader(this->Program, fs, GL_FRAGMENT_SHADER);

	GLint success =0;
	GLchar ErrorLog[512] = {0};
	glLinkProgram(this->Program);
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);

	if(success ==0) {
		glGetProgramInfoLog(this->Program, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr,"Error Link shader program:'%s' \n",ErrorLog);
		exit(5);
	}
	glValidateProgram(this->Program);
	glGetProgramiv(this->Program, GL_VALIDATE_STATUS, &success);
	if (!success) {
        glGetProgramInfoLog(this->Program, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(6);
    }
};
void  Shader::AddShader(GLuint ShaderProgram, const GLchar* pShaderText, 
					  GLenum ShaderType) {
	GLuint shader = glCreateShader(ShaderType);

	if(shader ==0) {
		fprintf(stderr, "Error createing shader type %d\n", ShaderType);
		exit(0);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	glShaderSource(shader, 1, p, Lengths);
	glCompileShader(shader);
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(shader, 1024, NULL, InfoLog);
		
		fprintf(stderr, "ERROR compiling shader type %d: '%s' \n",ShaderType, InfoLog);
		exit(1); 
	}
	glAttachShader(ShaderProgram, shader);
}
GLchar* Shader::readFile(char* filename )
{
#ifdef WIN32
	FILE* infile;
	fopen_s( &infile, filename, "rb" );
#else
    FILE* infile = fopen( filename, "rb" );
#endif // WIN32

    if ( !infile ) {
#ifdef _DEBUG
        std::cerr << "Unable to open file '" << filename << "'" << std::endl;
#endif /* DEBUG */
        return NULL;
    }

    fseek( infile, 0, SEEK_END );
    int len = ftell( infile );
    fseek( infile, 0, SEEK_SET );

    GLchar* source = new GLchar[len+1];
    fread( source, 1, len, infile );
    fclose( infile );

    source[len] = 0;

    return source;
}
void Shader::Use()
{
	glUseProgram(this->Program);
}