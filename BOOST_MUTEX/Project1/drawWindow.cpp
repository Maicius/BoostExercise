//#include "drawWindow.h"
//
//GLFWwindow* drawWindow::createGlfw(){
//	glfwInit();
//	//glfwWindowHint(GLFW_CURSOR_NORMAL, GL_FALSE);
//	//glfwWindowHint(GLFW_DECORATED, GL_FALSE);
//	int screenWidth =720 ;
//	int screenHeight = 720;
//	//glfwWindowHint(GLFW_DECORATED, GL_FALSE);
//	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Windows_1", NULL, NULL);
//	if(!window){
//		glfwTerminate();
//		std::cout<<"failed to create window"<<std::endl;
//		system("PAUSE");
//		exit(EXIT_FAILURE);
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//	glViewport(0, 0, screenWidth, screenHeight);
//	return window;
//}
//void drawWindow::Render(GLFWwindow* window, glm::vec2 mouseOffSet)
//{
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT);
//	GLfloat point[3][2] = { {-0.6f,-0.6f},{0.6f,-0.6f},{0.0f,0.6f} };
//	point[0][0]+=mouseOffSet.x;
//	point[0][1]+=mouseOffSet.y;
//	point[1][0]+=mouseOffSet.x;
//	point[1][1]+=mouseOffSet.y;
//	point[2][0]+=mouseOffSet.x;
//	point[2][1]+=mouseOffSet.y;
//	glBegin(GL_TRIANGLES);
//
//	glColor3f(1.0, 0.0, 0.0);    // Red
//	glVertex2fv(point[0]);
//
//	glColor3f(0.0, 1.0, 0.0);    // Green
//	glVertex2fv(point[1]);
//
//	glColor3f(0.0, 0.0, 1.0);    // Blue
//	glVertex2fv(point[2]);
//
//	glEnd();
//	glfwSwapBuffers(window);
//	glfwPollEvents();
//}
//
