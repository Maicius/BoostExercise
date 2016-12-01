
#include <iostream>
using namespace std;
#pragma comment(lib,"glfw3.lib")
#include <vgl.h>
#include <LoadShaders.h>
#include <GLFW/glfw3.h>
#include <GL/glew.h>
enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
const GLuint NumVertices = 6;
const GLchar* vertexShaderSource = 
	"#version 430 core\n"
	"layout(location = 0) in vec3 vPosition;\n"
	"out vec3 vertexColor;\n"
	"void main()\n"
	"	{	\n"
	"	gl_Position = vec4(vPosition, 1.0);\n"
	"   //vertexColor = vec4(1f, 1f, 0.0f, 1.0f);\n"
	"}\0";
const GLchar* fragmentShaderSource =
	"#version 430 core\n"
	"uniform vec4 vertexColor;\n"
	"out vec4 outColor;\n"
	"void main(){\n"
	"	ourColor = vertexColor;\n"
	"}\n\0";

//********************************************
//init
void init(void)
{
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);

	GLfloat vertices[NumVertices][2] = {
		{-0.90, -0.90}, //triangles1
		{ 0.85, -0.90},
		{-0.90,  0.85},
		{ 0.90, -0.85},	//triangles2
		{ 0.90,  0.90},
		{-0.85,  0.90}
	};

	

	/*******
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "triangles.vert"},
		{ GL_FRAGMENT_SHADER, "triangles.frag"},
		{ GL_NONE, NULL}
	};
	
	GLuint program = LoadShaders(shaders);
	*********/
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(vertexShader);
	GLint successVertex, successFragment, successProgram;
	std::cout<<"successVertex = "<<successVertex <<" address is:"<<&successVertex;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successVertex);
	if(!successVertex){
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout<<"ERROR::SHADER::VERTEX::COMPILE FAILED\n"<<infoLog<<std::endl;
	}else{
		std::cout<<"successVertex = "<<successVertex <<" address is:"<<&successVertex<<std::endl;
	}

	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFragment);
	if(!successFragment){
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout<<"ERROR::SHADER::Fragment::COMPILE FAILED\n"<<infoLog<<std::endl;		
	}else{
		std::cout<<"successFragment = "<<successFragment <<" address is:"<<&successFragment<<std::endl;
	}
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successProgram);
	if( !successProgram){
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout<<"ERROR::SHADER::PROGRAM::LINKING_FALED\n";
	}

	glUseProgram(shaderProgram);
	//glfwSetTime(0);
	GLfloat timeValue = glfwGetTime();
	GLfloat greenValue = (sin(timeValue)/2)+0.5;
	GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "vertexColor");
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, 
						  GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);
}

//***********************
//display
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(VAOs[Triangles]);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
	glFlush();
}

//**********************************************************
//main
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	//glfwInit();
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(argv[0]);

	glewExperimental = GL_TRUE;
	if (glewInit()) {
		cerr <<"Unable to initialize GLEW ... exiting"<<endl;
		exit(EXIT_FAILURE);
	}
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}