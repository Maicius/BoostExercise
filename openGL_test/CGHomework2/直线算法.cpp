// 画圆算法.cpp : 定义控制台应用程序的入口点。
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
		/*先用XOR模式清除刚才的圆*/
		glLogicOp(GL_XOR);
		bres(xm, ym, xmm, ymm);
		glFlush();

		/*绘制确定的圆*/
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
	/*非0，需要XOR清除刚才画的圆*/
	if (first == 1)
	{
		glLogicOp(GL_XOR);
		//glRectf(xm, ym, xmm, ymm);
		bres(xm, ym, xmm, ymm);
		glFlush();

	}

	/*获取新的移动坐标，绘制圆，并计数器标志定为1*/
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

	/* 设置背景色是黑色 */
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	/*开启逻辑运算功能！！！*/
	glEnable(GL_COLOR_LOGIC_OP);

	/*设置缓冲模式*/
	/*glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);*/


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/*裁剪窗口是一个单位正方形，坐标原点位于正方形的左下角*/
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

	/*注册需要的两个鼠标回调函数*/
	glutMouseFunc(mouse);
	glutMotionFunc(move);
	glutMainLoop();

}





