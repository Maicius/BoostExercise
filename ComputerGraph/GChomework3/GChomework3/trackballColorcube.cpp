// trackball.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


/* Rotating cube demo with trackball*/

#include <math.h>
#include <stdlib.h>
#include <GL/freeglut.h>

#define M_PI 3.14159

#define bool int
#define false 0
#define true 1

///*************10.26号加***/
int Near = 3;
int Far = 10;
int Zeye=5;
int projectStyle = 1;//1：平行正投影，2：透视
///***************************/

int 	winWidth=500, winHeight=500;
bool redrawContinue = false;
float lastPos[3] = { 0.0F, 0.0F, 0.0F };
float 	angle = 0.0;
GLfloat axis[3] = { 0.0, 0.0, 0.1 }; 
int curx, cury;
int startX, startY;

GLfloat vertices[4][3]={{0.0, 0.0, 1.0}, {0.0, 0.942809, -0.33333},
{-0.816497, -0.471405, -0.333333}, {0.816497, -0.471405, -0.333333}};
GLfloat colors[4][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0},
{0.0, 0.0, 1.0}, {1.0, 1.0, 0.0}};

void triangle(GLfloat *va, GLfloat *vb, GLfloat *vc)
{
	glVertex3fv(va);
	glVertex3fv(vb);
	glVertex3fv(vc);
}
void tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d)
{
	glBegin(GL_TRIANGLES);
	glColor3fv(colors[0]);
	triangle(a, b, c);
	glColor3fv(colors[1]);
	triangle(a, c, d);
	glColor3fv(colors[2]);
	triangle(a, d, b);
	glColor3fv(colors[3]);
	triangle(b, d, c);
	glEnd();
	glFlush();
}
void divide_tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, int m)
{

	GLfloat mid[6][3];
	int j;
	if(m>0)
	{
		/* compute six midpoints */

		for(j=0; j<3; j++) mid[0][j]=(a[j]+b[j])/2;
		for(j=0; j<3; j++) mid[1][j]=(a[j]+c[j])/2;
		for(j=0; j<3; j++) mid[2][j]=(a[j]+d[j])/2;
		for(j=0; j<3; j++) mid[3][j]=(b[j]+c[j])/2;
		for(j=0; j<3; j++) mid[4][j]=(c[j]+d[j])/2;
		for(j=0; j<3; j++) mid[5][j]=(b[j]+d[j])/2;

		/* create 4 tetrahedrons by subdivision */

		divide_tetra(a, mid[0], mid[1], mid[2], m-1);
		divide_tetra(mid[0], b, mid[3], mid[5], m-1);
		divide_tetra(mid[1], mid[3], c, mid[4], m-1);
		divide_tetra(mid[2], mid[4], d, mid[5], m-1);

	}
	else(tetra(a,b,c,d)); /* draw tetrahedron at end of recursion */
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

}

void stopMotion(int x, int y)
{
	/*||逻辑或，这里不太明白为什么加这个，去掉也不影响???*/
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
/*******************************************************************************************************************
主要修改部分：连续转动需要累积起组合变换矩阵，按顺序是左乘，但是写程序要按右乘来写
********************************************************************************************************************/
float  CompositeTransMatrix[4][4] = {{ 1.0, 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0, 0.0 }, { 0.0, 0.0, 0.0, 1.0 } };
float *p_CompositeTransMatrix = *CompositeTransMatrix;

float Mlookup[4][4] = {{ 1.0, 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0, 0.0 }, { 0.0, 0.0, 0.0, 1.0 } };;
float *p_Mlookup = *Mlookup;

void display()
{
	/*这条语句必须放在这里，以便每次绘制之前都需要清理颜色和深度缓存*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);	

	glLoadIdentity();
	/*设置视点相机位置，默认相机位置在原点，投影面是XOY平面,因为是左乘，所以让M初始值设为它*/
	gluLookAt(0, 0, Zeye, 0, 0, 0, 0, 1, 0);
	glGetFloatv(GL_MODELVIEW_MATRIX, p_Mlookup);


	/*多个旋转组合，理论上左乘顺序，而CTM实现是右乘属性。
	这里用栈操作实现不了顺序，只能靠自己编程设置矩阵保存上次旋转后的组合矩阵，再CTM右乘它
	公式为：CTM(i)=I*R(i)*M(i-1); M(i)=CTM(i）;初始：CTM(0)=I, M(0)=I*/
	glLoadIdentity();
	glRotatef(angle, axis[0], axis[1], axis[2]);
	glMultMatrixf(p_CompositeTransMatrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, p_CompositeTransMatrix);

	glLoadMatrixf(p_Mlookup);
	glMultMatrixf(p_CompositeTransMatrix);	

	//colorcube();
	divide_tetra(vertices[0], vertices[1], vertices[2], vertices[3], 3);
	/*注意这里采用的是立即显示，没有用动画模式，为得是让转动速度减慢
	如果采用双帧，则鼠标拖动时，立方体会转得非常快*/
	glFlush();
}

void myidle()
{
	if (redrawContinue == true)
	{
		//让自动动画转得慢一点，加了这句，固定速度自转，不根据交互鼠标拖动的速度继续平滑转动。
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
	//if (Botton == GLUT_RIGHT_BUTTON)

}

void Perspective(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-3, 3, -3, 3, 0, 4);
	if (w <= h)
		glFrustum(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,
		2.0 * (GLfloat)h / (GLfloat)w, Near, Far);
	else
		glFrustum(-2.0 * (GLfloat)w / (GLfloat)h,
		2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, Near, Far);
	glutPostRedisplay();

	//需要这两条语句，使得跟踪球交互操作正确
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

	//需要这两条语句，使得跟踪球交互操作正确
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
	}
}

void myReshape(int w, int h)
{
	if (projectStyle == 1)
		Orthographic(w, h);
	else
		Perspective(w, h);
}
int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("trackball Color Cube");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutIdleFunc(myidle);
	glutMouseFunc(myMouse);
	glutMotionFunc(mouseMotion);

	glutCreateMenu(Draw_menu);//菜单回调函数
	glutAddMenuEntry("Orthographic", 1);
	glutAddMenuEntry("Perspective", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
	glClearColor(1.0, 1.0, 1.0, 1.0);


	glutMainLoop();
}
