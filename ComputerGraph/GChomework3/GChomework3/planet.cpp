//// planet.cpp : 定义控制台应用程序的入口点。
////
//
//#include "stdafx.h"
//
//#define GLUT_DISABLE_ATEXIT_HACK   ；
//#include<GL/glut.h>
//#include<math.h>
//
//
//static int year = 0, day = 0;
//
//
//void init(void)
//{
//	glClearColor(0.0, 0.0, 0.0, 1.0);
//	//必须在创建窗口后写这条语句
//    glEnable(GL_DEPTH_TEST);
//	glShadeModel(GL_FLAT);
//}
//
//void display(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	//基本图元void glutWireSphere(GLdouble radius,GLint slices, GLint stacks);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//
//
//	//draw the sun
//	glColor3f(1.0, 0.0, 0.0);
//	glutSolidSphere(0.5, 20, 16);            //太阳，半径1.0
//
//	//draw the panet
//	glColor3f(0.0, 0.0, 1.0);
//	glRotatef((GLfloat)year, 0.0, 1.0, 0.0);   //绕太阳中心公转，角度为year
//
//	glTranslatef(2, 0.0, 0.0);              //距离太阳半径为2
//	glRotatef((GLfloat)day, 0.0, 1.0, 0.0);    //绕地球中心自转，角度为day
//	glutWireSphere(0.2, 10, 8);               //地球，半径0.2
//
//
//	//动画需要
//	glutSwapBuffers();
//}
//
//void reshape(int w, int h)
//{
//
//	int w1 = w;
//	int h1 = h;
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	//void gluPerspective( GLdouble   fovy,   GLdouble   aspect,    GLdouble   zNear,    GLdouble   zFar); 
//	gluPerspective(40.0, (GLfloat)w1 / (GLfloat)h1, 1.0, 20.0);//设置裁剪窗口，透视投影
//
//	glViewport(0, 0, w1, h1);//设置视口大小为屏幕窗口大小
//}
//
//void keyboard(unsigned char key, int x, int y)
//{
//	switch (key){
//	case 'd':
//		day = (day + 10) % 360;
//		glutPostRedisplay();
//		break;
//	case 'D':
//		day = (day - 10) % 360;
//		glutPostRedisplay();
//		break;
//	case 'y':
//		year = (year + 5) % 360;
//		glutPostRedisplay();
//		break;
//	case 'Y':
//		year = (year - 5) % 360;
//		glutPostRedisplay();
//		break;
//	default:
//		break;
//	}
//}
///*公转*/
//void revolution()
//{
//	year = (year + 1) % 360;
//	glutPostRedisplay();
//}
//void rotation()
//{
//	day = (day + 10) % 360;
//	glutPostRedisplay();
//}
//
//
//
//
//void mouse(int button, int state, int x, int y)
//{
//	switch (button){
//	case GLUT_LEFT_BUTTON:
//		if (state == GLUT_DOWN)
//			glutIdleFunc(revolution);
//		else
//			glutIdleFunc(NULL);
//		break;
//	case GLUT_RIGHT_BUTTON:
//		if (state == GLUT_DOWN)
//			glutIdleFunc(rotation);
//		else
//			glutIdleFunc(NULL);
//		break;
//
//	default:
//		break;
//	}
//}
//
//
//int main(int argc, char** argv)
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB|GLUT_DEPTH);
//	glutInitWindowSize(900, 700);
//	glutInitWindowPosition(0, 0);
//	glutCreateWindow(argv[0]);
//
//	init();
//
//	glutDisplayFunc(display);
//	glutReshapeFunc(reshape);
//	glutKeyboardFunc(keyboard);
//	glutMouseFunc(mouse);
//
//	glutMainLoop();
//	return 0;
//}
//
//
//
//
