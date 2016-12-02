#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/freeglut.h>
#include <glm.hpp>
#include <iostream>
#include "Shader.h"
struct Vector3f
{
    float x;
    float y;
    float z;
    Vector3f(){}
    Vector3f(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
};
class drawWindow{
private:
	int screenWidth, screenHeight;
	bool firstMouse;
public:
	drawWindow():screenWidth(1280), screenHeight(720){}
	GLFWwindow* drawWindow::createGlfw();
	GLuint createVertexBuffer();
	void Render(Shader shader, GLfloat* MVP ,GLuint VBO);
};