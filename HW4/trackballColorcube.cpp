// trackball.cpp : �������̨Ӧ�ó������ڵ㡣
//
/* Rotating cube demo with trackball*/
#include <math.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <iostream>
#include <SOIL.h>
#include <string>
#define M_PI 3.14159

#define bool int
#define false 0
#define true 1
typedef float point[4];

/* initial tetrahedron */

point v[] = { { 0.0, 0.0, 1.0 }, { 0.0, 0.942809, -0.33333 },
{ -0.816497, -0.471405, -0.333333 }, { 0.816497, -0.471405, -0.333333 } };
float  CompositeTransMatrix[4][4]= {{ 1.0, 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0, 0.0 }, { 0.0, 0.0, 0.0, 1.0 } };
float *p_CompositeTransMatrix = *CompositeTransMatrix;
GLuint texture1, texture2, texture3, texture4;
float Mlookup[4][4]= {{ 1.0, 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0, 0.0 }, { 0.0, 0.0, 0.0, 1.0 } };;
float *p_Mlookup = *Mlookup;
GLfloat colorR=1.0, colorG=0.0, colorB=0.0;
GLfloat color = 0.0;
/****************/
int mode;
int n;
int Near = 1.9;
int Far = 8;
int Zeye=5;
int projectStyle = 1;//1��ƽ����ͶӰ��2��͸��
/***************************/

int winWidth=1280, winHeight=720;
bool redrawContinue = false;
float lastPos[3] = { 0.0F, 0.0F, 0.0F };
float 	angle = 0.0;
GLfloat axis[3] = { 0.0, 0.0, 0.1 }; 
int curx, cury;
int startX, startY;
bool line_ball = false;


GLfloat vertices[][3] = {
	{ -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 }, { 1.0, 1.0, -1.0 }, { -1.0, 1.0, -1.0 },
	{ -1.0, -1.0, 1.0 }, { 1.0, -1.0, 1.0 }, { 1.0, 1.0, 1.0 }, { -1.0, 1.0, 1.0 }
};

GLfloat colors[][3] = {
	{ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 },
	{ 0.0, 0.0, 1.0 }, { 1.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 }, { 0.0, 1.0, 1.0 }
};
void polygon(int a, int b, int c, int d, int face);
void colorcube(void);
void trackball_ptov(int x, int y, int width, int height, float v[3]);
void mouseMotion(int x, int y);
void startMotion(int x, int y);
void stopMotion(int x, int y);
void tetrahedron(int m);
void display();
void myidle();
void myMouse(int Botton, int State, int MouseX, int MouseY);
void Perspective(int w, int h);
void Orthographic(int w, int h);
void Draw_menu(int index);
void myReshape(int w, int h);
void triangle(point a, point b, point c);
void normal(point p);
void divide_triangle(point a, point b, point c, int m);
void tetrahedron(int m);
void key_callback(unsigned char key, int x, int y);
void myinit();
GLuint generateTexture(const char* texture_name);
int main(int argc, char **argv)
{
	n=5;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("HW5");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutIdleFunc(myidle);
	glutMouseFunc(myMouse);
	glutMotionFunc(mouseMotion);
	myinit();
	texture1=generateTexture("texture.png");
	texture2=generateTexture("wall.jpg");
	texture3=generateTexture("xuzifan.jpg");
	texture4=generateTexture("texture_a.png");
	glutCreateMenu(Draw_menu);//�˵��ص�����
	glutAddMenuEntry("Orthographic", 1);
	glutAddMenuEntry("Perspective", 2);
	glutAddMenuEntry("line_ball",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutKeyboardFunc(key_callback);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glutMainLoop();
}

GLuint generateTexture(const char* texture_name)
{
	GLuint texture;
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int texWidth, texHeight;
	unsigned char  *image = SOIL_load_image(texture_name,&texWidth, &texHeight, 0, SOIL_LOAD_RGBA);
	if(image== NULL)
		std::cout<<"Failed to load Image:"<<texture_name<<std::endl;
    
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, texWidth, texHeight, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	//glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

void polygon(int a, int b, int c, int d, int face)
{

	/* draw a polygon via list of vertices */
	
	glBegin(GL_POLYGON);
	//glActiveTexture(GL_TEXTURE0);
	glTexCoord2f(0.0f, 1.0f);
	glColor3fv(colors[a]);
	glVertex3fv(vertices[a]);

	glTexCoord2f(1.0f, 1.0f);
	glColor3fv(colors[b]);
	glVertex3fv(vertices[b]);

	glTexCoord2f(1.0f, 0.0f);
	glColor3fv(colors[c]);
	glVertex3fv(vertices[c]);

	glTexCoord2f(0.0f, 0.0f);
	glColor3fv(colors[d]);
	glVertex3fv(vertices[d]);
	glEnd();
}

void colorcube(void)
{

	/* map vertices to faces */
	glBindTexture(GL_TEXTURE_2D, texture4);
	polygon(1, 0, 3, 2, 0);
	glBindTexture(GL_TEXTURE_2D, texture3);
	polygon(3, 7, 6, 2, 1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glBindTexture(GL_TEXTURE_2D, texture4);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	polygon(7, 3, 0, 4, 2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	polygon(2, 6, 5, 1, 3);
	glBindTexture(GL_TEXTURE_2D, texture4);
	polygon(4, 5, 6, 7, 4);
	glBindTexture(GL_TEXTURE_2D, texture2);
	polygon(5, 4, 0, 1, 5);
}

/*----------------------------------------------------------------------*/
/*** These functions implement a simple trackball-like motion control.
-------------------------------------------------------------------------*/
void trackball_ptov(int x, int y, int width, int height, float v[3])
{
	float d, a;

	v[0] = (2.0F*x - width) / width;
	v[1] = (height - 2.0F*y) / height;
	d = (float)sqrt(v[0] * v[0] + v[1] * v[1]);
	v[2] = (float)cos((M_PI / 2.0F) * ((d < 1.0F) ? d : 1.0F));
	a = 1.0F / (float)sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] *= a;
	v[1] *= a;
	v[2] *= a;
}

void mouseMotion(int x, int y)
{
	float curPos[3], dx, dy, dz;
	trackball_ptov(x, y, winWidth, winHeight, curPos);

	dx = curPos[0] - lastPos[0];
	dy = curPos[1] - lastPos[1];
	dz = curPos[2] - lastPos[2];

	if (dx || dy || dz) {
		angle = 90.0F * sqrt(dx*dx + dy*dy + dz*dz);

		axis[0] = lastPos[1] * curPos[2] - lastPos[2] * curPos[1];
		axis[1] = lastPos[2] * curPos[0] - lastPos[0] * curPos[2];
		axis[2] = lastPos[0] * curPos[1] - lastPos[1] * curPos[0];

		lastPos[0] = curPos[0];
		lastPos[1] = curPos[1];
		lastPos[2] = curPos[2];
	}

	glutPostRedisplay();
}

void startMotion(int x, int y)
{
	redrawContinue = false;
	startX = x; startY = y;
	curx = x; cury = y;
	trackball_ptov(x, y, winWidth, winHeight, lastPos);
	colorR = std::abs(sin(x));
	colorG = std::abs(cos(y));
	colorB = std::abs(sin(y));
	//std::cout<<"colorR:"<<colorR<<std::endl;
}

void stopMotion(int x, int y)
{
	/*||�߼������ﲻ̫����Ϊʲô�������ȥ��Ҳ��Ӱ��???*/
	/*
	if (startX != x || startY != y)
	{
	redrawContinue = true;
	}
	else
	{
	angle = 0.0F;
	redrawContinue = false;
	}
	*/

	redrawContinue = true;

}
void tetrahedron(int m)
{

	/* Apply triangle subdivision to faces of tetrahedron */
	divide_triangle(v[0], v[1], v[2], m);
	divide_triangle(v[3], v[2], v[1], m);
	divide_triangle(v[0], v[3], v[1], m);
	divide_triangle(v[0], v[2], v[3], m);
}
/*******************************************************************************************************************
��Ҫ�޸Ĳ��֣�����ת����Ҫ�ۻ�����ϱ任���󣬰�˳������ˣ�����д����Ҫ���ҳ���д
********************************************************************************************************************/


void display()
{
	/*�����������������Ա�ÿ�λ���֮ǰ����Ҫ������ɫ����Ȼ���*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glBindTexture(GL_TEXTURE_2D, texture);
	glMatrixMode(GL_MODELVIEW);	

	glLoadIdentity();
	/*�����ӵ����λ�ã�Ĭ�����λ����ԭ�㣬ͶӰ����XOYƽ��,��Ϊ����ˣ�������M��ʼֵ��Ϊ��*/
	gluLookAt(0, 0, Zeye, 0, 0, 0, 0, 1, 0);
	glGetFloatv(GL_MODELVIEW_MATRIX, p_Mlookup);
	/*�����ת��ϣ����������˳�򣬶�CTMʵ�����ҳ����ԡ�
	������ջ����ʵ�ֲ���˳��ֻ�ܿ��Լ�������þ��󱣴��ϴ���ת�����Ͼ�����CTM�ҳ���
	��ʽΪ��CTM(i)=I*R(i)*M(i-1); M(i)=CTM(i��;��ʼ��CTM(0)=I, M(0)=I*/


	glLoadIdentity();
	glRotatef(angle, axis[0], axis[1], axis[2]);
	glMultMatrixf(p_CompositeTransMatrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, p_CompositeTransMatrix);

	glLoadMatrixf(p_Mlookup);
	glMultMatrixf(p_CompositeTransMatrix);
	mode = 0;
	if(line_ball) tetrahedron(n);
	mode = 1;
	glTranslatef(-2.0, 0.0, 0.0);
	tetrahedron(n);
	mode = 2;
	glTranslatef(4.0, 0.0, 0.0);
	colorcube();

	/*ע��������õ���������ʾ��û���ö���ģʽ��Ϊ������ת���ٶȼ���
	�������˫֡��������϶�ʱ���������ת�÷ǳ���*/
	glFlush();
}

void myidle()
{
	myinit();
	if (redrawContinue == true)
	{
		//���Զ�����ת����һ�㣬������䣬�̶��ٶ���ת�������ݽ�������϶����ٶȼ���ƽ��ת����
		angle = 0.1;
		//std::cout << angle << std::endl;

		glutPostRedisplay();
	}
}


void myMouse(int Botton, int State, int MouseX, int MouseY)
{
	if (Botton == GLUT_LEFT_BUTTON)
	{
		switch (State)
		{
		case GLUT_DOWN:
			//angle = 0;
			//MouseY = WinHeight - MouseY;
			startMotion(MouseX, MouseY);
			break;
		case GLUT_UP:
			stopMotion(MouseX, MouseY);
			break;
		}
	}

}

void Perspective(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glFrustum(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,
		2.0 * (GLfloat)h / (GLfloat)w, Near, Far);
	else
		glFrustum(-2.0 * (GLfloat)w / (GLfloat)h,
		2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, Near, Far);
	//glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();

	//��Ҫ��������䣬ʹ�ø����򽻻�������ȷ
	winWidth = w;
	winHeight = h;
}

void Orthographic(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,
		2.0 * (GLfloat)h / (GLfloat)w, Near, Far);
	else
		glOrtho(-2.0 * (GLfloat)w / (GLfloat)h,
		2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, Near,Far);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();

	//��Ҫ��������䣬ʹ�ø����򽻻�������ȷ
	winWidth = w;
	winHeight = h;
}
void Draw_menu(int index)
{
	switch (index)
	{
	case (1) :
		{
			Orthographic(winWidth, winHeight);
			projectStyle = 1;
			glutPostRedisplay();
			break;
		}

	case (2) :
		{
			Perspective(winWidth, winHeight);				 
			projectStyle = 2;
			glutPostRedisplay();
			break;
		}
	case(3):
		{
			if(line_ball == false)
				line_ball = true;
			else
				line_ball =false;
			display();
			break;
		}
	}
}

void myReshape(int w, int h)
{
	if (projectStyle == 1)
		Orthographic(w, h);
	else
		Perspective(w, h);
}



void triangle(point a, point b, point c)
{
	/* display one triangle using a line loop for wire frame, a single
	normal for constant shading, or three normals for interpolative shading */
    glBindTexture(GL_TEXTURE_2D, texture2);
	if (mode == 0) glBegin(GL_LINE_LOOP);	else glBegin(GL_POLYGON);

	if (mode == 1) glNormal3fv(a);

	if (mode == 2) glNormal3fv(a);
	glTexCoord2fv(a);
	glVertex3fv(a);
	if (mode == 2) glNormal3fv(b);
	glTexCoord2fv(b);
	glVertex3fv(b);
	if (mode == 2) glNormal3fv(c);
	glTexCoord2fv(c);
	glVertex3fv(c);
	glEnd();
}

void normal(point p)
{

	/* normalize a vector */
	double sqrt();
	float d = 0.0;
	int i;
	for (i = 0; i<3; i++) d += p[i] * p[i];
	//d = sqrt(d);
	d = sqrtf(d);
	if (d>0.0) for (i = 0; i<3; i++) p[i] /= d;
}

void divide_triangle(point a, point b, point c, int m)
{

	/* triangle subdivision using vertex numbers
	righthand rule applied to create outward pointing faces */

	point v1, v2, v3;
	int j;
	if (m>0)
	{
		for (j = 0; j<3; j++) v1[j] = a[j] + b[j];
		normal(v1);
		for (j = 0; j<3; j++) v2[j] = a[j] + c[j];
		normal(v2);
		for (j = 0; j<3; j++) v3[j] = b[j] + c[j];
		normal(v3);
		divide_triangle(a, v1, v2, m - 1);
		divide_triangle(c, v2, v3, m - 1);
		divide_triangle(b, v3, v1, m - 1);
		divide_triangle(v1, v3, v2, m - 1);
	}
	else(triangle(a, b, c)); /* draw triangle at end of recursion */
}

void myinit()
{
	GLfloat mat_specular[] = { colorR, colorG, colorB, 1.0 };
	GLfloat mat_diffuse[] = { colorR, colorG, colorB, 1.0 };
	GLfloat mat_ambient[] = { colorR, colorG, colorB, 1.0 };
	GLfloat mat_shininess = { 100.0 };
	GLfloat light_ambient[] = { 1, 0.2, 0.2, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = {0.0, 0.0, 0.0, 1.0};
	/* set up ambient, diffuse, and specular components for light 0 */

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	/* define material proerties for front face of all polygons */

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	glShadeModel(GL_SMOOTH); /*enable smooth shading */
	glEnable(GL_LIGHTING); /* enable lighting */
	glEnable(GL_LIGHT0);  /* enable light 0 */
	glEnable(GL_DEPTH_TEST); /* enable z buffer */

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
}
void key_callback(unsigned char key, int x, int y){
	//std::cout<<"������ݹ����N>>";
	int number = (int)key;
	if(number < 48 || number > 55){
	}
	else{
		std::cout<<number-48<<std::endl;
		n = number-48;
		display();
	}
}
