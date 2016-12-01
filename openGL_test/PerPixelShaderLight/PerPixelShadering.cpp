//#include <iostream>
//#include <GL/glew.h>
//#include <GL/freeglut.h>
//using namespace std;
//
//GLuint VBOPosition, VBONormal;
//GLint LightLocation, LightIntenLocation;
//GLint DiffuseLocation, AmbientLocation, SpecularLocation, ShininessLocation;
//GLint ModelViewLocation, NormalLocation, ProjectionLocation, MVPLocation;
//GLuint ShaderProgram;
//class Vector3f{
//private:
//	float x, y, z;
//public:
//	Vector3f(){};
//	Vector3f(float x, float y, float z){
//		this->x = x;
//		this->y = y;
//		this->z = z;
//	}
//};
//static void RenderSceneCB()
//{
//	glUseProgram(ShaderProgram);
//    glClear(GL_COLOR_BUFFER_BIT);
//	glEnableVertexAttribArray(0);
//	//glEnableVertexAttribArray(1);
//	glBindBuffer(GL_ARRAY_BUFFER, VBOPosition);
//	//glBindBuffer(GL_ARRAY_BUFFER, VBONormal);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);	
//	glDrawArrays(GL_TRIANGLES, 0, 9);
//	glDisableVertexAttribArray(0);
//	GLfloat ModelViewMatrix[16] ={1.0f, 1.0f, 1.0f, 1.0f,
//								1.0f, 1.0f, 1.0f, 1.0f,
//								1.0f, 1.0f, 1.0f, 1.0f,
//								1.0f, 1.0f, 1.0f, 1.0f};
//
//	GLfloat NormalMatrix[9] ={1.0f, 1.0f, 1.0f,
//							1.0f,1.0f, 1.0f, 
//							1.0f, 1.0f,1.0f};
//
//	GLfloat ProjectionMatrix[16] = {1.0f, 1.0f, 1.0f, 1.0f,
//					1.0f, 1.0f, 1.0f, 1.0f,
//					1.0f, 1.0f, 1.0f, 1.0f,
//					1.0f, 1.0f, 1.0f, 1.0f};
//
//	GLfloat MVP[16] ={1.0f, 1.0f, 1.0f, 1.0f,
//					1.0f, 1.0f, 1.0f, 0.0f,
//					0.0f, 1.0f, 1.0f, 0.0f,
//					1.0f, 0.0f, 0.0f, 1.0f};
//	GLfloat LightPosition[4] = {1.0f, 1.0f, 1.0f, 1.0f};
//	GLfloat Specular[3] = {0.3f, 0.3f, 0.3f};
//	GLfloat LightInten[3] = {0.9f, 0.9f, 0.9f};
//	GLfloat DiffuseRelec[3] = {0.5f, 0.5f, 0.5f};
//	GLfloat AmbientRelec[3] = {1.0f, 0.5f, 0.7f};
//	GLfloat Shininess = 0.4f;
//
//	GLfloat VertexPosition[3] = {0.5f, 0.5f, 0.5f};
//	GLfloat VertexNormal[3] = {0.6f, 0.6f, 0.6f};
//	glUniformMatrix4fv(ModelViewLocation,1,GL_TRUE, ModelViewMatrix);
//	glUniformMatrix3fv(NormalLocation, 1, GL_TRUE, NormalMatrix);
//	glUniformMatrix4fv(ProjectionLocation, 1, GL_TRUE, ProjectionMatrix);
//	glUniformMatrix4fv(MVPLocation, 1, GL_TRUE, MVP);
//	glUniform3fv(SpecularLocation, 3, Specular);
//	glUniform4fv(LightLocation, 4, LightPosition);
//	glUniform3fv(LightIntenLocation, 3, LightInten);
//	glUniform3fv(DiffuseLocation, 3, DiffuseRelec);
//	glUniform3fv(AmbientLocation, 3, AmbientRelec);
//	glUniform3fv(ShininessLocation, 1, &Shininess);
//    glutSwapBuffers();
//}
//
//static void CreateVertexBuffer(){
//	Vector3f Vertices[3];
//	Vertices[0] = Vector3f(0.9f, 0.9f, 0.0f);
//	Vertices[1] = Vector3f(-0.9f, 0.9f, 0.0f);
//	Vertices[2] = Vector3f(0.0f, -1.0f, 0.0f);
//
//	glGenBuffers(1, &VBOPosition);
//	glBindBuffer(GL_ARRAY_BUFFER, VBOPosition);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
//}
//
//static void AddShader(GLuint ShaderProgram, const GLchar* pShaderText, 
//					  GLenum ShaderType) {
//	GLuint shader = glCreateShader(ShaderType);
//
//	if(shader ==0) {
//		fprintf(stderr, "Error createing shader type %d\n", ShaderType);
//		exit(0);
//	}
//
//	const GLchar* p[1];
//	p[0] = pShaderText;
//	GLint Lengths[1];
//	Lengths[0] = strlen(pShaderText);
//	glShaderSource(shader, 1, p, Lengths);
//	glCompileShader(shader);
//	GLint success;
//	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//	if(!success) {
//		GLchar InfoLog[1024];
//		glGetShaderInfoLog(shader, 1024, NULL, InfoLog);
//		fprintf(stderr, "ERROR compiling shader type %d: '%s' \n",ShaderType, InfoLog);
//		exit(1); 
//	}
//	glAttachShader(ShaderProgram, shader);
//}
//static GLchar* readFile(char* filename )
//{
//#ifdef WIN32
//	FILE* infile;
//	fopen_s( &infile, filename, "rb" );
//#else
//    FILE* infile = fopen( filename, "rb" );
//#endif // WIN32
//
//    if ( !infile ) {
//#ifdef _DEBUG
//        std::cerr << "Unable to open file '" << filename << "'" << std::endl;
//#endif /* DEBUG */
//        return NULL;
//    }
//
//    fseek( infile, 0, SEEK_END );
//    int len = ftell( infile );
//    fseek( infile, 0, SEEK_SET );
//
//    GLchar* source = new GLchar[len+1];
//    fread( source, 1, len, infile );
//    fclose( infile );
//
//    source[len] = 0;
//
//    return source;
//}
//
//
//static void CompileShaders()
//{
//	ShaderProgram = glCreateProgram();
//
//	if(ShaderProgram ==0) {
//		fprintf(stderr, "Error to create shader program");
//		exit(2);
//	}
//	GLchar *fs;
//	fs = readFile("perFrag.frag");
//	GLchar *vs;
//	vs = readFile("perVertex.vert");
//    AddShader(ShaderProgram, vs, GL_VERTEX_SHADER);
//    AddShader(ShaderProgram, fs, GL_FRAGMENT_SHADER);
//
//	GLint success =0;
//	GLchar ErrorLog[512] = {0};
//	glLinkProgram(ShaderProgram);
//	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
//
//	if(success ==0) {
//		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
//		fprintf(stderr,"Error Link shader program:'%s' \n",ErrorLog);
//		exit(5);
//	}
//	glValidateProgram(ShaderProgram);
//	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &success);
//	if (!success) {
//        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
//        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
//        exit(6);
//    }
//	glUseProgram(ShaderProgram);
//	
//	ModelViewLocation = glGetUniformLocation(ShaderProgram, "ModelViewMatirx");
//	NormalLocation = glGetUniformLocation(ShaderProgram, "NormalMatrix");
//	ProjectionLocation = glGetUniformLocation(ShaderProgram, "ProjectionMatrix");
//	MVPLocation = glGetUniformLocation(ShaderProgram, "MVP");
//	LightLocation = glGetUniformLocation(ShaderProgram, "LightPosition");
//	LightIntenLocation = glGetUniformLocation(ShaderProgram, "LightIntensity");
//	DiffuseLocation = glGetUniformLocation(ShaderProgram, "Diffuse");
//	AmbientLocation = glGetUniformLocation(ShaderProgram, "Ambient");
//	SpecularLocation = glGetUniformLocation(ShaderProgram, "Specular");
//	ShininessLocation = glGetUniformLocation(ShaderProgram, "Shininess");
//}
//
//int main(int argc, char* argv[])
//{
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
//    glutInitWindowSize(1024, 768);
//    glutInitWindowPosition(100, 100);
//    glutCreateWindow("PER PIXEL SHADERING");
//		
//	glewExperimental = GL_TRUE;
//	if (glewInit()) {
//		cerr <<"Unable to initialize GLEW ... exiting"<<endl;
//		exit(EXIT_FAILURE);
//	}
//    CreateVertexBuffer();
//	glutDisplayFunc(RenderSceneCB);
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//	CompileShaders();
//    glutMainLoop();
//
//    return 0;
//}