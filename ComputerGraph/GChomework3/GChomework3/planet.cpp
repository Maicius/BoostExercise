//// planet.cpp : �������̨Ӧ�ó������ڵ㡣
////
//
//#include "stdafx.h"
//
//#define GLUT_DISABLE_ATEXIT_HACK   ��
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
//	//�����ڴ������ں�д�������
//    glEnable(GL_DEPTH_TEST);
//	glShadeModel(GL_FLAT);
//}
//
//void display(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	//����ͼԪvoid glutWireSphere(GLdouble radius,GLint slices, GLint stacks);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//
//
//	//draw the sun
//	glColor3f(1.0, 0.0, 0.0);
//	glutSolidSphere(0.5, 20, 16);            //̫�����뾶1.0
//
//	//draw the panet
//	glColor3f(0.0, 0.0, 1.0);
//	glRotatef((GLfloat)year, 0.0, 1.0, 0.0);   //��̫�����Ĺ�ת���Ƕ�Ϊyear
//
//	glTranslatef(2, 0.0, 0.0);              //����̫���뾶Ϊ2
//	glRotatef((GLfloat)day, 0.0, 1.0, 0.0);    //�Ƶ���������ת���Ƕ�Ϊday
//	glutWireSphere(0.2, 10, 8);               //���򣬰뾶0.2
//
//
//	//������Ҫ
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
//	gluPerspective(40.0, (GLfloat)w1 / (GLfloat)h1, 1.0, 20.0);//���òü����ڣ�͸��ͶӰ
//
//	glViewport(0, 0, w1, h1);//�����ӿڴ�СΪ��Ļ���ڴ�С
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
///*��ת*/
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
