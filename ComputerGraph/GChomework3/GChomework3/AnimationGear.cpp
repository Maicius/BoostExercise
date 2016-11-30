///**1）避免破帧：单帧和双帧切换示例程序，
//2）层次建模采用矩阵栈操作
//3) 动画时间控制-增加
//*/
//
//#include "openGL/freeglut.h"
//#include "math.h "
//#include "time.h"
//
//
////////Traversing hierarchical data structures-采用矩阵栈操作/////
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
////从原始齿轮进行缩放和平移，得到基本齿轮tooth1
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
////让基本齿轮tooth1（每个次轮12度)依着大圆每旋转12度画一次，得到全周长的gear:12*30=360度
//void gear(double r)
//{
//	glPushMatrix();
//	//每次旋转12度，画一个齿轮tooth1
//	for (int i = 1; i <= 30; ++i) {
//		tooth1(r);
//		glRotatef(12.0, 0.0, 0.0, 1.0);
//	}
//	glPopMatrix();
//}
////////Traversing hierarchical data structures-采用矩阵栈操作/////
//
///*******************单帧和双帧切换****************************************/
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
///********************使用时间控制动画****************************************/
//float deg = 0.0; //全局变量
//void  display()  {
//	glClear(GL_COLOR_BUFFER_BIT);
//	glColor3f(0.0, 1.0, 0.0);
//	glPushMatrix();
//	glRotatef(deg, 0.0, 0.0, 1.0);// 新增语句
//	gear(1.0);
//	glPopMatrix();
//	glutSwapBuffers();
//}
//int oldTime = clock(), newTime;//初始化，程序开始就是第一次的oldtime
//void  move()  {
//	//每秒24变化帧，以上才能实现动画，否则很停顿，
//	float speed = 0.01;
//	newTime = clock();//clock()获取单位是毫秒
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
//*******************使用时间控制动画****************************************/
///*******************单帧和双帧切换****************************************/
//
//
//
//
//void myReshape(int w, int h)
//{
//	glViewport(0, 0, w, h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	//根据视口的纵横比w/h，反过来调整投影窗口范围，注意由于该窗口是依坐标对称的。
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
//	/*******************单帧和双帧切换****************************************/
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//	/*******************单帧和双帧切换****************************************/
//
//	glutInitWindowSize(500, 500);
//	glutCreateWindow("A moving gear wheel-double frame");
//	glutDisplayFunc(display);
//	glutReshapeFunc(myReshape);
//
//	/**********************动画函数****************************/
//	glutIdleFunc(move);//这句不能放在前面去
//	/**********************动画函数****************************/
//
//	init();
//	glutMainLoop();
//	return 0;
//}
//
//
