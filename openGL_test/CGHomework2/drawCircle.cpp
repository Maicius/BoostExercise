//#include <GL/freeglut.h>
//#include <math.h>
//#include <iostream>
//const int R = 40;
//const float PI = 3.14;
//int mouseX = 0, mouseY = 0;
//int shiftX = 0, shiftY = 0;
//bool FirstClick = true;
//int first = 0;
//void mouse(int btn, int state, int x, int y);
//void move(int x, int y);
//void drawCircle();
//void Render();
//void init()
//{
//	glClearColor(1, 1.0, 1, 1);
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	/*开启逻辑运算功能！！！*/
//	glEnable(GL_COLOR_LOGIC_OP);
//	glMatrixMode(GL_PROJECTION);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//	glLoadIdentity();
//	gluOrtho2D(0, 700, 0, 700);
//}
//int main(int argc, char *argv[])
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(700, 700);
//	glutCreateWindow("DrawCircle");
//	init();
//	glutDisplayFunc(Render);
//	glutMouseFunc(mouse);
//	glutMotionFunc(move);
//	glutMainLoop();
//}
//void mouse(int btn, int state, int x, int y){
//	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
//		
//		mouseX = x;
//		mouseY =700 - y;
//		std::cout<<"圆心：（"<<x<<", "<<y<<")"<<std::endl;
//		drawCircle();
//		first = 0;
//	}
//	
//
//}
//void move(int x, int y){
//	shiftX = x - mouseX;
//	shiftY = 700 - y - mouseY;
//	drawCircle();
//	mouseX = x;
//	mouseY = y;	
//	glutPostRedisplay();
//}
//
//void drawCircle()
//{
//	int n = 20;
//	glClear(GL_COLOR_BUFFER_BIT);
//	glBegin(GL_LINE_LOOP);
//     for(int i=0; i<n; ++i){
//		 glColor3f(0.5 ,0.5, 0.5);
//		 glVertex2f(mouseX + R*cos(2*PI/n*i)+shiftX,mouseY + R*sin(2*PI/n*i)+shiftY);
//	 }
//    glEnd();
//	//for(int i = mouseX-R; i <= mouseX+R;i++){
//	//	double j = sqrt((R*R - (i-mouseX)*(i-mouseX))) + mouseY;
//	//	//std::cout<<"i-mouseX;"<<i-mouseX<<"   R:"<<R<<std::endl;
//	//	drawPixel(i, j);
//	//	j = -sqrt((R*R - (i-mouseX)*(i-mouseX))) + mouseY;
//	//	drawPixel(i, j);
//	//}
//}
//void Render()
//{
//	glFlush();
//}