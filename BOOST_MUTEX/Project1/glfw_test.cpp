//#include <GLFW/glfw3.h>
//#include <GL/freeglut.h>
//#include <iostream>
//
//void display(){
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//	float Left[3] = {-0.6f, -0.6f, 0.0f};
//	float Top[3] = {0.0f, 0.6f, 0.0f};
//	float Right[3] = {0.6f, -0.6f, 0.0f};
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glBegin(GL_TRIANGLES);
//	glColor3f(1.0f, 1.0f, 1.0f);
//	glVertex3fv(Top);
//	glVertex3fv(Left);
//	glVertex3fv(Right);
//	glEnd();
//}
//int main(){
//	glfwInit();
//	int screenWidth = 1280;
//	int screenHeight = 720;
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_PROFILE);
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//	glfwWindowHint(GLFW_DECORATED, GL_FALSE);
//	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Windows_1", NULL, NULL);
//	if(!window){
//		glfwTerminate();
//		std::cout<<"failed to create window"<<std::endl;
//		system("PAUSE");
//		exit(EXIT_FAILURE);
//	}
//	glfwMakeContextCurrent(window);
//	glViewport(0, 0, screenWidth, screenHeight);
//	while(!glfwWindowShouldClose(window)){
//		display();
//		glfwSwapBuffers(window);
//	}
//	glfwTerminate();
//
//}
//
