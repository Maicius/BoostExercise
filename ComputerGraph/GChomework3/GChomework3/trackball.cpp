//// trackball.cpp : �������̨Ӧ�ó������ڵ㡣
////
//
//#include "stdafx.h"
//
//
///* Rotating cube demo with trackball*/
//
//#include <math.h>
//#include <stdlib.h>
//#include <GL/freeglut.h>
//
//#define M_PI 3.14159
//
//#define bool int
//#define false 0
//#define true 1
//
/////*************10.26�ż�***/
//int Near = 3;
//int Far = 10;
//int Zeye=5;
//int projectStyle = 1;//1��ƽ����ͶӰ��2��͸��
/////***************************/
//
//int 	winWidth=500, winHeight=500;
//bool redrawContinue = false;
//float lastPos[3] = { 0.0F, 0.0F, 0.0F };
//float 	angle = 0.0;
//GLfloat axis[3] = { 0.0, 0.0, 0.1 }; 
//int curx, cury;
//int startX, startY;
//
//
//
////GLfloat vertices[][3] = {
////	{ -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 }, { 1.0, 1.0, -1.0 }, { -1.0, 1.0, -1.0 },
////	{ -1.0, -1.0, 1.0 }, { 1.0, -1.0, 1.0 }, { 1.0, 1.0, 1.0 }, { -1.0, 1.0, 1.0 }
////};
//GLfloat vertices[4][3]={{0.0, 0.0, 1.0}, {0.0, 0.942809, -0.33333},
//      {-0.816497, -0.471405, -0.333333}, {0.816497, -0.471405, -0.333333}};
//GLfloat colors[4][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0},
//                        {0.0, 0.0, 1.0}, {1.0, 1.0, 0.0}};
////GLfloat colors[][3] = {
////	{ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 },
////	{ 0.0, 0.0, 1.0 }, { 1.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 }, { 0.0, 1.0, 1.0 }
////};
//
//
//void polygon(int a, int b, int c, int face)
//{
//
//	/* draw a polygon via list of vertices */
//
//	glBegin(GL_POLYGON);
//	glColor3fv(colors[a]);
//	glVertex3fv(vertices[a]);
//	glColor3fv(colors[b]);
//	glVertex3fv(vertices[b]);
//	glColor3fv(colors[c]);
//	glVertex3fv(vertices[c]);
//	//glColor3fv(colors[d]);
//	//glVertex3fv(vertices[d]);
//	glEnd();
//}
//
//void colorcube(void)
//{
//
//	/* map vertices to faces */
//
//	//polygon(1, 0, 3, 2, 0);
//	//polygon(3, 7, 6, 2, 1);
//	//polygon(7, 3, 0, 4, 2);
//	//polygon(2, 6, 5, 1, 3);
//	//polygon(4, 5, 6, 7, 4);
//	//polygon(5, 4, 0, 1, 5);
//	polygon(0, 1, 2, 0);
//	polygon(0, 1, 3, 1);
//	polygon(1, 2, 3, 2);
//	polygon(0, 2, 3, 3);
//}
//
///*----------------------------------------------------------------------*/
///*** These functions implement a simple trackball-like motion control.
//-------------------------------------------------------------------------*/
//void trackball_ptov(int x, int y, int width, int height, float v[3])
//{
//	float d, a;
//
//	v[0] = (2.0F*x - width) / width;
//	v[1] = (height - 2.0F*y) / height;
//	d = (float)sqrt(v[0] * v[0] + v[1] * v[1]);
//	v[2] = (float)cos((M_PI / 2.0F) * ((d < 1.0F) ? d : 1.0F));
//	a = 1.0F / (float)sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
//	v[0] *= a;
//	v[1] *= a;
//	v[2] *= a;
//}
//
//void mouseMotion(int x, int y)
//{
//	float curPos[3], dx, dy, dz;
//	trackball_ptov(x, y, winWidth, winHeight, curPos);
//
//	dx = curPos[0] - lastPos[0];
//	dy = curPos[1] - lastPos[1];
//	dz = curPos[2] - lastPos[2];
//
//	if (dx || dy || dz) {
//		angle = 90.0F * sqrt(dx*dx + dy*dy + dz*dz);
//
//		axis[0] = lastPos[1] * curPos[2] - lastPos[2] * curPos[1];
//		axis[1] = lastPos[2] * curPos[0] - lastPos[0] * curPos[2];
//		axis[2] = lastPos[0] * curPos[1] - lastPos[1] * curPos[0];
//
//		lastPos[0] = curPos[0];
//		lastPos[1] = curPos[1];
//		lastPos[2] = curPos[2];
//	}
//
//	glutPostRedisplay();
//}
//
//void startMotion(int x, int y)
//{
//	redrawContinue = false;
//	startX = x; startY = y;
//	curx = x; cury = y;
//	trackball_ptov(x, y, winWidth, winHeight, lastPos);
//
//}
//
//void stopMotion(int x, int y)
//{
//	/*||�߼������ﲻ̫����Ϊʲô�������ȥ��Ҳ��Ӱ��???*/
//	/*
//	if (startX != x || startY != y)
//	{
//		redrawContinue = true;
//	}
//	else
//	{
//		angle = 0.0F;
//		redrawContinue = false;
//	}
//	*/
//	redrawContinue = true;
//
//}
///*******************************************************************************************************************
//��Ҫ�޸Ĳ��֣�����ת����Ҫ�ۻ�����ϱ任���󣬰�˳������ˣ�����д����Ҫ���ҳ���д
//********************************************************************************************************************/
//float  CompositeTransMatrix[4][4] = {{ 1.0, 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0, 0.0 }, { 0.0, 0.0, 0.0, 1.0 } };
//float *p_CompositeTransMatrix = *CompositeTransMatrix;
//
//float Mlookup[4][4] = {{ 1.0, 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0, 0.0 }, { 0.0, 0.0, 0.0, 1.0 } };;
//float *p_Mlookup = *Mlookup;
//
//void display()
//{
//	/*�����������������Ա�ÿ�λ���֮ǰ����Ҫ������ɫ����Ȼ���*/
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	
//	glMatrixMode(GL_MODELVIEW);	
//
//	glLoadIdentity();
//	/*�����ӵ����λ�ã�Ĭ�����λ����ԭ�㣬ͶӰ����XOYƽ��,��Ϊ����ˣ�������M��ʼֵ��Ϊ��*/
//	gluLookAt(0, 0, Zeye, 0, 0, 0, 0, 1, 0);
//	glGetFloatv(GL_MODELVIEW_MATRIX, p_Mlookup);
//	
//
//	/*�����ת��ϣ����������˳�򣬶�CTMʵ�����ҳ����ԡ�
//	������ջ����ʵ�ֲ���˳��ֻ�ܿ��Լ�������þ��󱣴��ϴ���ת�����Ͼ�����CTM�ҳ���
//	��ʽΪ��CTM(i)=I*R(i)*M(i-1); M(i)=CTM(i��;��ʼ��CTM(0)=I, M(0)=I*/
//	glLoadIdentity();
//	glRotatef(angle, axis[0], axis[1], axis[2]);
//	glMultMatrixf(p_CompositeTransMatrix);
//	glGetFloatv(GL_MODELVIEW_MATRIX, p_CompositeTransMatrix);
//
//	glLoadMatrixf(p_Mlookup);
//	glMultMatrixf(p_CompositeTransMatrix);	
//	
//	colorcube();
//	
//	/*ע��������õ���������ʾ��û���ö���ģʽ��Ϊ������ת���ٶȼ���
//	�������˫֡��������϶�ʱ���������ת�÷ǳ���*/
//	glFlush();
//}
//
//void myidle()
//{
//	if (redrawContinue == true)
//	{
//		//���Զ�����ת����һ�㣬������䣬�̶��ٶ���ת�������ݽ�������϶����ٶȼ���ƽ��ת����
//		angle = 0.1;
//		//std::cout << angle << std::endl;
//
//		glutPostRedisplay();
//	}
//
//}
//
//
//void myMouse(int Botton, int State, int MouseX, int MouseY)
//{
//	if (Botton == GLUT_LEFT_BUTTON)
//	{
//		switch (State)
//		{
//		case GLUT_DOWN:
//			//angle = 0;
//			//MouseY = WinHeight - MouseY;
//			startMotion(MouseX, MouseY);
//			break;
//		case GLUT_UP:
//			stopMotion(MouseX, MouseY);
//			break;
//		}
//	}
//	//if (Botton == GLUT_RIGHT_BUTTON)
//		
//}
//
//void Perspective(int w, int h)
//{
//	glViewport(0, 0, w, h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	//glFrustum(-3, 3, -3, 3, 0, 4);
//	if (w <= h)
//		glFrustum(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,
//		2.0 * (GLfloat)h / (GLfloat)w, Near, Far);
//	else
//		glFrustum(-2.0 * (GLfloat)w / (GLfloat)h,
//		2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, Near, Far);
//	glutPostRedisplay();
//
//	//��Ҫ��������䣬ʹ�ø����򽻻�������ȷ
//	winWidth = w;
//	winHeight = h;
//}
//
//void Orthographic(int w, int h)
//{
//	glViewport(0, 0, w, h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	if (w <= h)
//		glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,
//		2.0 * (GLfloat)h / (GLfloat)w, Near, Far);
//	else
//		glOrtho(-2.0 * (GLfloat)w / (GLfloat)h,
//		2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, Near,Far);
//	glMatrixMode(GL_MODELVIEW);
//	glutPostRedisplay();
//
//	//��Ҫ��������䣬ʹ�ø����򽻻�������ȷ
//	winWidth = w;
//	winHeight = h;
//
//}
//void Draw_menu(int index)
//{
//	switch (index)
//	{
//	case (1) :
//	{
//				 Orthographic(winWidth, winHeight);
//				 projectStyle = 1;
//				 glutPostRedisplay();
//				 break;
//	}
//
//	case (2) :
//	{
//				 Perspective(winWidth, winHeight);				 
//				 projectStyle = 2;
//				 glutPostRedisplay();
//				 break;
//	}
//	}
//}
//
//void myReshape(int w, int h)
//{
//	if (projectStyle == 1)
//		Orthographic(w, h);
//	else
//		Perspective(w, h);
//}
//int main(int argc, char **argv)
//{
//
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
//	glutInitWindowSize(winWidth, winHeight);
//	glutCreateWindow("trackball Color Cube");
//	glutReshapeFunc(myReshape);
//	glutDisplayFunc(display);
//	glutIdleFunc(myidle);
//	glutMouseFunc(myMouse);
//	glutMotionFunc(mouseMotion);
//
//	glutCreateMenu(Draw_menu);//�˵��ص�����
//	glutAddMenuEntry("Orthographic", 1);
//	glutAddMenuEntry("Perspective", 2);
//	glutAttachMenu(GLUT_RIGHT_BUTTON);
//
//	glEnable(GL_DEPTH_TEST);
//	glShadeModel(GL_FLAT);
//	glClearColor(1.0, 1.0, 1.0, 1.0);
//
//	
//	glutMainLoop();
//}