// ��Բ�㷨.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include <stdlib.h>
#include <openGL/freeglut.h>         /* glut.h includes gl.h and glu.h*/
#include <math.h>
#include <iostream>

int xm, ym, xmm, ymm;
int first = 0;
const float PI = 3.14;
void draw_pixel(int ix, int iy)
{
	glBegin(GL_POINTS);
	glVertex2i(ix, iy);
	glEnd();
}

void bres(int x1, int y1, int x2, int y2)
{
	int dx, dy, i, e;
	int incx, incy, inc1, inc2;
	int x, y;
	x = x1;
	y = y1;
	dx = (x2 - x1);
	dy = (y2 - y1);
	float R = sqrt((dx*dx) + (dy*dy));//radius
	int n =40;
	glBegin(GL_LINE_LOOP);
	for(int i=0; i<n; ++i){
		glColor3f(0.5 ,0.5, 0.5);
		//Equation: C = (x^2+R*cos(PI/n),y^2 + R*sin(PI/n))
		glVertex2f(x2 + R*cos(2*PI/n*i),y2 + R*sin(2*PI/n*i));
	}
	glEnd();
	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	incx = 1;
	if (x2 < x1) incx = -1;
	incy = 1;
	if (y2 < y1) incy = -1;


	if (dx > dy)
	{
		draw_pixel(x, y);
		e = 2 * dy - dx;
		inc1 = 2 * (dy - dx);
		inc2 = 2 * dy;
		for (i = 0; i < dx; i++)
		{
			if (e >= 0)
			{
				y += incy;
				e += inc1;
			}
			else e += inc2;
			x += incx;
			draw_pixel(x, y);
		}
	}
	else
	{
		draw_pixel(x, y);
		e = 2 * dx - dy;
		inc1 = 2 * (dx - dy);
		inc2 = 2 * dx;
		for (i = 0; i < dy; i++)
		{
			if (e >= 0)
			{
				x += incx;
				e += inc1;
			}
			else e += inc2;
			y += incy;
			draw_pixel(x, y);
		}
	}

}


void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		xm = x;
		ym = (700 - y);
		glColor3f(1.0, 1.0, 1.0);
		first = 0;
	}
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		/*����XORģʽ����ղŵ�Բ*/
		glLogicOp(GL_XOR);
		bres(xm, ym, xmm, ymm);
		glFlush();

		/*����ȷ����Բ*/
		xmm = x;
		ymm = (700 - y);
		glColor3f(1.0, 1.0, 1.0);
		bres(xm, ym, xmm, ymm);
		glFlush();
		glLogicOp(GL_COPY);
	}
}

void move(int x, int y)
{
	/*��0����ҪXOR����ղŻ���Բ*/
	if (first == 1)
	{
		glLogicOp(GL_XOR);
		//glRectf(xm, ym, xmm, ymm);
		bres(xm, ym, xmm, ymm);
		glFlush();

	}

	/*��ȡ�µ��ƶ����꣬����Բ������������־��Ϊ1*/
	xmm = x;
	ymm = (700 - y);
	glColor3f(1.0, 1.0, 1.0);
	bres(xm, ym, xmm, ymm);
	glFlush();
	first = 1;
}

void display()
{
	glFlush();
}


void init()
{

	/* ���ñ���ɫ�Ǻ�ɫ */
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	/*�����߼����㹦�ܣ�����*/
	glEnable(GL_COLOR_LOGIC_OP);

	/*���û���ģʽ*/
	/*glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);*/


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/*�ü�������һ����λ�����Σ�����ԭ��λ�������ε����½�*/
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	gluOrtho2D(0, 700, 0, 700);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);          // Initialize GLUT function callings
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Line");

	init();
	glutDisplayFunc(display);

	/*ע����Ҫ���������ص�����*/
	glutMouseFunc(mouse);
	glutMotionFunc(move);
	glutMainLoop();

}





