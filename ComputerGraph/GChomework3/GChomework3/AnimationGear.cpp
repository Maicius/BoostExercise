///**1��������֡����֡��˫֡�л�ʾ������
//2����ν�ģ���þ���ջ����
//3) ����ʱ�����-����
//*/
//
//#include "openGL/freeglut.h"
//#include "math.h "
//#include "time.h"
//
//
////////Traversing hierarchical data structures-���þ���ջ����/////
//void  tooth0()  {
//	glBegin(GL_LINE_STRIP);
//	glVertex2f(0.0, 0.0);
//	glVertex2f(0.2, 0.2);
//	glVertex2f(0.6, 0.2);
//	glVertex2f(0.6, 0.8);
//	glVertex2f(0.2, 0.8);
//	glVertex2f(0.0, 1.0);
//	glEnd();
//}
//
////��ԭʼ���ֽ������ź�ƽ�ƣ��õ���������tooth1
//void  tooth1(double  r)  {
//	double rad = 6.0 * 3.1416 / 180.0,
//		sin6 = r * sin(rad), cos6 = r * cos(rad);
//	glPushMatrix();
//	glTranslatef(cos6, -sin6, 0.0);
//	glScalef(2.0*sin6, 2.0*sin6, 1.0);
//	tooth0();
//	glPopMatrix();
//}
//
////�û�������tooth1��ÿ������12��)���Ŵ�Բÿ��ת12�Ȼ�һ�Σ��õ�ȫ�ܳ���gear:12*30=360��
//void gear(double r)
//{
//	glPushMatrix();
//	//ÿ����ת12�ȣ���һ������tooth1
//	for (int i = 1; i <= 30; ++i) {
//		tooth1(r);
//		glRotatef(12.0, 0.0, 0.0, 1.0);
//	}
//	glPopMatrix();
//}
////////Traversing hierarchical data structures-���þ���ջ����/////
//
///*******************��֡��˫֡�л�****************************************/
///*
//void  display()  {
//	glColor3f(0.0, 1.0, 0.0);
//	for (int i = 1; i <= 100000; ++i) {
//		glClear(GL_COLOR_BUFFER_BIT);
//		glRotatef(0.1, 0.0, 0.0, 1.0);
//		gear(1.0);
//		glFlush();
//	}
//}
//*/
///********************ʹ��ʱ����ƶ���****************************************/
//float deg = 0.0; //ȫ�ֱ���
//void  display()  {
//	glClear(GL_COLOR_BUFFER_BIT);
//	glColor3f(0.0, 1.0, 0.0);
//	glPushMatrix();
//	glRotatef(deg, 0.0, 0.0, 1.0);// �������
//	gear(1.0);
//	glPopMatrix();
//	glutSwapBuffers();
//}
//int oldTime = clock(), newTime;//��ʼ��������ʼ���ǵ�һ�ε�oldtime
//void  move()  {
//	//ÿ��24�仯֡�����ϲ���ʵ�ֶ����������ͣ�٣�
//	float speed = 0.01;
//	newTime = clock();//clock()��ȡ��λ�Ǻ���
//	//deg += (newTime - oldTime) * speed;
//	deg += (newTime - oldTime) * speed;
//	oldTime = newTime;
//	glutPostRedisplay();
//}
///*
//void  move()  {
//	glRotatef(0.1, 0.0, 0.0, 1.0);
//	glutPostRedisplay();
//}
//*******************ʹ��ʱ����ƶ���****************************************/
///*******************��֡��˫֡�л�****************************************/
//
//
//
//
//void myReshape(int w, int h)
//{
//	glViewport(0, 0, w, h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	//�����ӿڵ��ݺ��w/h������������ͶӰ���ڷ�Χ��ע�����ڸô�����������ԳƵġ�
//	//aspect = w / h;
//	if (w <= h)
//		gluOrtho2D(-2.0, 2.0, -2.0 * h / w, 2.0 * h / w);
//	else
//		gluOrtho2D(-2.0 * w / h, 2.0 * w / h, -2.0, 2.0);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//}
//
//
//
//
//void  init()  {
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D(-1.2, 1.2, -1.2, 1.2);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//}
//
//
//int  main(int argc, char **argv)  {
//	glutInit(&argc, argv);
//	/*******************��֡��˫֡�л�****************************************/
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//	/*******************��֡��˫֡�л�****************************************/
//
//	glutInitWindowSize(500, 500);
//	glutCreateWindow("A moving gear wheel-double frame");
//	glutDisplayFunc(display);
//	glutReshapeFunc(myReshape);
//
//	/**********************��������****************************/
//	glutIdleFunc(move);//��䲻�ܷ���ǰ��ȥ
//	/**********************��������****************************/
//
//	init();
//	glutMainLoop();
//	return 0;
//}
//
//
