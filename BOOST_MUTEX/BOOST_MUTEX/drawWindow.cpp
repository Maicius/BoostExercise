#include "drawWindow.h"

GLFWwindow* drawWindow::createGlfw(){
	glfwInit();
	int screenWidth =480 ;
	int screenHeight = 480;
	//glfwWindowHint(GLFW_DECORATED, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Windows_1", NULL, NULL);
	if(!window){
		glfwTerminate();
		std::cout<<"failed to create window"<<std::endl;
		system("PAUSE");
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glViewport(0, 0, screenWidth, screenHeight);
	return window;
}
GLuint drawWindow::createVertexBuffer()
{
	GLuint VBO;
    Vector3f Vertices[3];
    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
    Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
    Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices,GL_STATIC_DRAW);
	return VBO;
}
void drawWindow::Render(Shader shader, GLfloat* MVP, GLuint VBO)
{
	shader.Use();
	GLint MVPLocation = glGetUniformLocation(shader.Program, "MVP");
	glUniformMatrix4fv(MVPLocation, 1, GL_TRUE, MVP);

    glClear(GL_COLOR_BUFFER_BIT);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}

