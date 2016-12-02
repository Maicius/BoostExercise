//#include <GLFW/glfw3.h>
//#include <GL/freeglut.h>
//int main(void)
//{
//	glfwInit();
//	
//	//glfwWindowHint(GLFW_CURSOR_, GL_FALSE);
//	GLFWwindow* window = glfwCreateWindow(480, 320, "Hello World", NULL, NULL);
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//	if (!window)
//	{
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//
//	while (!glfwWindowShouldClose(window))
//	{
//		glBegin(GL_TRIANGLES);
//		GLfloat point[3][2] = { {-0.6f,-0.6f},{0.6f,-0.6f},{0.0f,0.6f} };
//		glColor3f(1.0, 0.0, 0.0);    // Red
//		glVertex2fv(point[0]);
//		glColor3f(0.0, 1.0, 0.0);    // Green
//		glVertex2fv(point[1]);
//
//		glColor3f(0.0, 0.0, 1.0);    // Blue
//		glVertex2fv(point[2]);
//
//		glEnd();
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	glfwTerminate();
//	return 0;
//}