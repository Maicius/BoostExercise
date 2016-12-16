//// trackball.cpp : �������̨Ӧ�ó������ڵ㡣
////
///* Rotating cube demo with trackball*/
//
//#include <math.h>
//#include <stdlib.h>
//#include <GL/freeglut.h>
//#include <iostream>
//#define M_PI 3.14159
//
//#define bool int
//#define false 0
//#define true 1
//typedef float point[4];
//
///* initial tetrahedron */
//
//point v[] = { { 0.0, 0.0, 1.0 }, { 0.0, 0.942809, -0.33333 },
//{ -0.816497, -0.471405, -0.333333 }, { 0.816497, -0.471405, -0.333333 } };
//float  CompositeTransMatrix[4][4]= {{ 1.0, 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0, 0.0 }, { 0.0, 0.0, 0.0, 1.0 } };
//float *p_CompositeTransMatrix = *CompositeTransMatrix;
//
//float Mlookup[4][4]= {{ 1.0, 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0, 0.0 }, { 0.0, 0.0, 0.0, 1.0 } };;
//float *p_Mlookup = *Mlookup;
//
//
///****************/
//int mode;
//int n;
//int Near = 3;
//int Far = 10;
//int Zeye=5;
//int projectStyle = 1;//1��ƽ����ͶӰ��2��͸��
///***************************/
//
//int winWidth=500, winHeight=500;
//bool redrawContinue = false;
//float lastPos[3] = { 0.0F, 0.0F, 0.0F };
//float 	angle = 0.0;
//GLfloat axis[3] = { 0.0, 0.0, 0.1 }; 
//int curx, cury;
//int startX, startY;
//
//
//
//GLfloat vertices[][3] = {
//	{ -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 }, { 1.0, 1.0, -1.0 }, { -1.0, 1.0, -1.0 },
//	{ -1.0, -1.0, 1.0 }, { 1.0, -1.0, 1.0 }, { 1.0, 1.0, 1.0 }, { -1.0, 1.0, 1.0 }
//};
//
//GLfloat colors[][3] = {
//	{ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 },
//	{ 0.0, 0.0, 1.0 }, { 1.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 }, { 0.0, 1.0, 1.0 }
//};
//void polygon(int a, int b, int c, int d, int face);
//void colorcube(void);
//void trackball_ptov(int x, int y, int width, int height, float v[3]);
//void mouseMotion(int x, int y);
//void startMotion(int x, int y);
//void stopMotion(int x, int y);
//void tetrahedron(int m);
//void display();
//void myidle();
//void myMouse(int Botton, int State, int MouseX, int MouseY);
//void myReshape(int w, int h);
//void triangle(point a, point b, point c);
//void normal(point p);
//void divide_triangle(point a, point b, point c, int m);
//void tetrahedron(int m);
//void key_callback(unsigned char key, int x, int y);
//void myinit();
//
//int main(int argc, char **argv)
//{
//	n=5;
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
//	glutInitWindowSize(winWidth, winHeight);
//	glutCreateWindow("Trackball with light");
//	myinit();
//	glutReshapeFunc(myReshape);
//	glutDisplayFunc(display);
//	glutIdleFunc(myidle);
//	glutMouseFunc(myMouse);
//	glutMotionFunc(mouseMotion);
//	glutKeyboardFunc(key_callback);
//	glEnable(GL_DEPTH_TEST);
//	glShadeModel(GL_FLAT);
//	glClearColor(1.0, 1.0, 1.0, 1.0);
//
//	glutMainLoop();
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
//void tetrahedron(int m)
//{
//
//	/* Apply triangle subdivision to faces of tetrahedron */
//	divide_triangle(v[0], v[1], v[2], m);
//	divide_triangle(v[3], v[2], v[1], m);
//	divide_triangle(v[0], v[3], v[1], m);
//	divide_triangle(v[0], v[2], v[3], m);
//}
///*******************************************************************************************************************
//��Ҫ�޸Ĳ��֣�����ת����Ҫ�ۻ�����ϱ任���󣬰�˳������ˣ�����д����Ҫ���ҳ���д
//********************************************************************************************************************/
//
//
//void display()
//{
//	/*�����������������Ա�ÿ�λ���֮ǰ����Ҫ������ɫ����Ȼ���*/
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	
//	//glMatrixMode(GL_MODELVIEW);	
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
//	mode = 0;
//	tetrahedron(n);
//	mode = 1;
//	glTranslatef(-2.0, 0.0, 0.0);
//	tetrahedron(n);
//	mode = 2;
//	glTranslatef(4.0, 0.0, 0.0);
//	tetrahedron(n);
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
//
//void myReshape(int w, int h)
//{
//	glViewport(0, 0, w, h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	if (w <= h)
//		glOrtho(-4.0, 4.0, -4.0 * (GLfloat)h / (GLfloat)w,
//		4.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
//	else
//		glOrtho(-4.0 * (GLfloat)w / (GLfloat)h,
//		4.0 * (GLfloat)w / (GLfloat)h, -4.0, 4.0, -10.0, 10.0);
//	glMatrixMode(GL_MODELVIEW);
//	display();
//}
//
//
//
//void triangle(point a, point b, point c)
//
///* display one triangle using a line loop for wire frame, a single
//normal for constant shading, or three normals for interpolative shading */
//{
//	if (mode == 0) glBegin(GL_LINE_LOOP);	else glBegin(GL_POLYGON);
//
//	if (mode == 1) glNormal3fv(a);
//
//	if (mode == 2) glNormal3fv(a);
//	glVertex3fv(a);
//	if (mode == 2) glNormal3fv(b);
//	glVertex3fv(b);
//	if (mode == 2) glNormal3fv(c);
//	glVertex3fv(c);
//	glEnd();
//}
//
//void normal(point p)
//{
//
//	/* normalize a vector */
//	double sqrt();
//	float d = 0.0;
//	int i;
//	for (i = 0; i<3; i++) d += p[i] * p[i];
//	//d = sqrt(d);
//	d = sqrtf(d);
//	if (d>0.0) for (i = 0; i<3; i++) p[i] /= d;
//}
//
//void divide_triangle(point a, point b, point c, int m)
//{
//
//	/* triangle subdivision using vertex numbers
//	righthand rule applied to create outward pointing faces */
//
//	point v1, v2, v3;
//	int j;
//	if (m>0)
//	{
//		for (j = 0; j<3; j++) v1[j] = a[j] + b[j];
//		normal(v1);
//		for (j = 0; j<3; j++) v2[j] = a[j] + c[j];
//		normal(v2);
//		for (j = 0; j<3; j++) v3[j] = b[j] + c[j];
//		normal(v3);
//		divide_triangle(a, v1, v2, m - 1);
//		divide_triangle(c, v2, v3, m - 1);
//		divide_triangle(b, v3, v1, m - 1);
//		divide_triangle(v1, v3, v2, m - 1);
//	}
//	else(triangle(a, b, c)); /* draw triangle at end of recursion */
//}
//
//void myinit()
//{
//	GLfloat mat_specular[] = { 1.0, 0.0, 0.0, 1.0 };
//	GLfloat mat_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
//	GLfloat mat_ambient[] = { 1.0, 0.0, 0.0, 1.0 };
//
//	GLfloat mat_shininess = { 100.0 };
//	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
//	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
//	GLfloat light_specular[] = { 0.0, 1.0, 1.0, 1.0 };
//
//	GLfloat light_position[] = {0.0, 0.0, 0.0, 1.0};
//	/* set up ambient, diffuse, and specular components for light 0 */
//
//	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
//	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//	/* define material proerties for front face of all polygons */
//	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
//	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
//	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
//
//	glShadeModel(GL_SMOOTH); /*enable smooth shading */
//	glEnable(GL_LIGHTING); /* enable lighting */
//	glEnable(GL_LIGHT0);  /* enable light 0 */
//	glEnable(GL_DEPTH_TEST); /* enable z buffer */
//
//	glClearColor(1.0, 1.0, 1.0, 1.0);
//	glColor3f(0.0, 0.0, 0.0);
//}
//void key_callback(unsigned char key, int x, int y){
//	//std::cout<<"������ݹ����N>>";
//	int number = (int)key;
//	if(number < 48 || number > 55){
//	}
//	else{
//		std::cout<<number-48<<std::endl;
//		n = number-48;
//		display();
//	}
//}
