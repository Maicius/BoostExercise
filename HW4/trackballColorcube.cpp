// trackball.cpp : 定义控制台应用程序的入口点。
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

//point v2[] =  {{ 0.0, 0.0, 4 }, { 0.0, 5.4, -1.8 },
//{ -4.8, -2.5, -1.8 }, { 4.8, -2.5, -1.8 } };

point v2[] =  {{ 0.0, 0.0, 6 }, { 0.0, 5.4, -1.8 },
{ -4.8, -2.5, -1.8 }, { 4.8, -2.5, -1.8 } };
float  CompositeTransMatrix[4][4]= {{ 1.0, 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0, 0.0 }, { 0.0, 0.0, 0.0, 1.0 } };
float *p_CompositeTransMatrix = *CompositeTransMatrix;
GLuint texture1, texture2, texture3, texture4,texture5;
float Mlookup[4][4]= {{ 1.0, 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0, 0.0 }, { 0.0, 0.0, 0.0, 1.0 } };;
float *p_Mlookup = *Mlookup;
GLfloat colorR=1.0, colorG=0.0, colorB=0.0;
GLfloat color = 0.0;
/****************/
int mode;
int n;
int Near = 1.9;
int Far = 100;
int Zeye=5;
int projectStyle = 1;//1：平行正投影，2：透视
/***************************/

int winWidth=1280, winHeight=720;
bool redrawContinue = false;
float lastPos[3] = { 0.0F, 0.0F, 0.0F };
float 	angle = 0.0;
GLfloat axis[3] = { 0.0, 0.0, 0.1 }; 
int curx, cury;
int startX, startY;
bool line_ball = false;
bool alpha_test = true;
bool show_background = false;
bool change_background = false;
GLfloat view_size=2.0;
char* alpha_string = "Enable or Disable Alpha";
GLfloat vertices[][3] = {
	{ -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 }, { 1.0, 1.0, -1.0 }, { -1.0, 1.0, -1.0 },
	{ -1.0, -1.0, 1.0 }, { 1.0, -1.0, 1.0 }, { 1.0, 1.0, 1.0 }, { -1.0, 1.0, 1.0 }
};
int size = 50;
GLfloat verticesBig[][3] = {
	{ -size, -size, -size }, { size, -size, -size }, { size, size, -size }, { -size, size, -size },
	{ -size, -size, size }, { size, -size, size }, { size, size, size }, { -size, size, size }
};

GLfloat colors[][3] = {
	{ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 },
	{ 0.0, 0.0, 1.0 }, { 1.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 }, { 0.0, 1.0, 1.0 }
};
void polygon(int a, int b, int c, int d, int face);
void polygonBig(int a, int b, int c, int d, int face);
void colorcube(void);
void colorcubeBig(void);
void trackball_ptov(int x, int y, int width, int height, float v[3]);
void mouseMotion(int x, int y);
void startMotion(int x, int y);
void stopMotion(int x, int y);
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
void tetrahedron2(int m);
void key_callback(unsigned char key, int x, int y);
void myinit();
void divide_triangle2(point a, point b, point c, int m);
void triangle2(point a, point b, point c);
GLuint generateTexture(const char* texture_name);
int main(int argc, char **argv)
{
	n=5;
	glutInit(&argc, argv);
	std::cout<<"*********************计图第五次作业****************************"<<std::endl;
	std::cout<<"*       键盘输入0-7可以查看三面体递归生成球体过程             *"<<std::endl;
	std::cout<<"*            鼠标每次点击画面会改变光源颜色                   *"<<std::endl;
	std::cout<<"*            键盘输入'-'或'+'可以改变视角的远近               *"<<std::endl;
	std::cout<<"*            键盘输入'-'或'+'可以改变视角的远近               *"<<std::endl;
	std::cout<<"*菜单选择*\n*1:平行投影*\n*2:透视投影*\n*3:打开或关闭中心的线框球*\n*4:打开或关闭Alpha通道(透明通道)*\n*启用Skybox*\n*改变Skybox主题"<<std::endl;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("HW5");
	glutInitWindowPosition(500, 500);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutIdleFunc(myidle);
	glutMouseFunc(myMouse);
	glutMotionFunc(mouseMotion);
	myinit();
	texture1=generateTexture("gundam.png");
	texture2=generateTexture("wall.png");
	texture3=generateTexture("xuzifan.png");
	texture4=generateTexture("xiaoqingx.jpg");
	texture5=generateTexture("sky.png");
	glutCreateMenu(Draw_menu);//菜单回调函数
	glutAddMenuEntry("Orthographic", 1);
	glutAddMenuEntry("Perspective", 2);
	glutAddMenuEntry("Enable or Disable Line_ball",3);	
	glutAddMenuEntry(alpha_string, 4);
	glutAddMenuEntry("Show or Hide Skybox",5);
	glutAddMenuEntry("Change Skybox",6);
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
	//glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, texWidth, texHeight, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glEnable(GL_TEXTURE_2D);
	//glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

void polygon(int a, int b, int c, int d, int face)
{

	/* draw a polygon via list of vertices */

	glBegin(GL_POLYGON);
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
void polygonBig(int a, int b, int c, int d, int face)
{

	/* draw a polygon via list of vertices */

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 1.0f);
	glColor3fv(colors[a]);
	glVertex3fv(verticesBig[a]);

	glTexCoord2f(1.0f, 1.0f);
	glColor3fv(colors[b]);
	glVertex3fv(verticesBig[b]);

	glTexCoord2f(1.0f, 0.0f);
	glColor3fv(colors[c]);
	glVertex3fv(verticesBig[c]);

	glTexCoord2f(0.0f, 0.0f);
	glColor3fv(colors[d]);
	glVertex3fv(verticesBig[d]);
	glEnd();
}

void colorcube(void)
{

	/* map vertices to faces */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, texture1);
	polygon(1, 0, 3, 2, 0);
	glBindTexture(GL_TEXTURE_2D, texture3);
	polygon(3, 7, 6, 2, 1);	
	glBindTexture(GL_TEXTURE_2D, texture2);
	polygon(7, 3, 0, 4, 2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	polygon(2, 6, 5, 1, 3);
	glBindTexture(GL_TEXTURE_2D, texture1);
	polygon(4, 5, 6, 7, 4);
	glBindTexture(GL_TEXTURE_2D, texture2);
	polygon(5, 4, 0, 1, 5);
}
void colorcubeBig(void)
{

	/* map vertices to faces */
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, texture5);
	polygonBig(1, 0, 3, 2, 0);
	polygonBig(3, 7, 6, 2, 1);	
	polygonBig(7, 3, 0, 4, 2);
	polygonBig(2, 6, 5, 1, 3);
	polygonBig(4, 5, 6, 7, 4);
	polygonBig(5, 4, 0, 1, 5);
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
void tetrahedron(int m)
{

	/* Apply triangle subdivision to faces of tetrahedron */
	divide_triangle(v[0], v[1], v[2], m);
	divide_triangle(v[3], v[2], v[1], m);
	divide_triangle(v[0], v[3], v[1], m);
	divide_triangle(v[0], v[2], v[3], m);
}
void tetrahedron2(int m)
{

	/* Apply triangle subdivision to faces of tetrahedron */
	divide_triangle2(v2[0], v2[1], v2[2], m);
	divide_triangle2(v2[3], v2[2], v2[1], m);
	divide_triangle2(v2[0], v2[3], v2[1], m);
	divide_triangle2(v2[0], v2[2], v2[3], m);
}
/*******************************************************************************************************************
主要修改部分：连续转动需要累积起组合变换矩阵，按顺序是左乘，但是写程序要按右乘来写
********************************************************************************************************************/
//void drawCircle(){
//	glBegin(GL_QUADS);
//}
void display()
{
	/*这条语句必须放在这里，以便每次绘制之前都需要清理颜色和深度缓存*/
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);	

	glLoadIdentity();
	/*设置视点相机位置，默认相机位置在原点，投影面是XOY平面,因为是左乘，所以让M初始值设为它*/
	gluLookAt(0, 0, Zeye, 0, 0, 0, 0, 1, 0);
	glGetFloatv(GL_MODELVIEW_MATRIX, p_Mlookup);
	/*多个旋转组合，理论上左乘顺序，而CTM实现是右乘属性。
	这里用栈操作实现不了顺序，只能靠自己编程设置矩阵保存上次旋转后的组合矩阵，再CTM右乘它
	公式为：CTM(i)=I*R(i)*M(i-1); M(i)=CTM(i）;初始：CTM(0)=I, M(0)=I*/
	if(alpha_test==true){
		glEnable(GL_BLEND);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0);
		
	}
	else if(alpha_test==false){
		glDisable(GL_BLEND);
		glDisable(GL_ALPHA_TEST);
	}

	glLoadIdentity();
	glRotatef(angle, axis[0], axis[1], axis[2]);
	glMultMatrixf(p_CompositeTransMatrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, p_CompositeTransMatrix);

	glLoadMatrixf(p_Mlookup);
	glMultMatrixf(p_CompositeTransMatrix);
	mode = 0;
	if(line_ball) tetrahedron(n);
	mode = 1;
	if(show_background){
		if(change_background) 
			colorcubeBig();
		else
		    tetrahedron2(3);
	}
	glTranslatef(-2.0, 0.0, 0.0);
	tetrahedron(n);
	mode = 2;
	glTranslatef(4, 0.0, 0.0);
	colorcube();

	/*注意这里采用的是立即显示，没有用动画模式，为得是让转动速度减慢
	如果采用双帧，则鼠标拖动时，立方体会转得非常快*/
	glFlush();
}

void myidle()
{
	myinit();
	myReshape(winWidth, winHeight);
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
}

void Perspective(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glFrustum(-view_size, view_size, -view_size * (GLfloat)h / (GLfloat)w,
		view_size * (GLfloat)h / (GLfloat)w, Near, Far);
	else
		glFrustum(-view_size * (GLfloat)w / (GLfloat)h,
		view_size * (GLfloat)w / (GLfloat)h, -view_size, view_size, Near, Far);
	//glMatrixMode(GL_MODELVIEW);
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
		glOrtho(-view_size, view_size, -view_size * (GLfloat)h / (GLfloat)w,
		view_size * (GLfloat)h / (GLfloat)w, Near, Far);
	else
		glOrtho(-view_size * (GLfloat)w / (GLfloat)h,
		view_size * (GLfloat)w / (GLfloat)h, -view_size, view_size, Near,Far);
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
	case(3):
		{
			if(!line_ball)
				line_ball = true;
			else
				line_ball =false;
			display();
			break;
		}
	case(4):
		{
			if(alpha_test == false){
				alpha_test = true;
				alpha_string="Disable_alpha";
			}
			else{
				alpha_test = false;
				alpha_string="Enable_alpha";
			}
			display();
			break;
		}
	case(5):
		{
			if(show_background) show_background=false;
			else show_background=true;
			display();
			break;
		}
	case(6):
		{
			if(change_background){ 
				change_background=false;
				show_background=true;
			}
			else change_background=true;
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
void triangle2(point a, point b, point c)
{
	/* display one triangle using a line loop for wire frame, a single
	normal for constant shading, or three normals for interpolative shading */
	glBindTexture(GL_TEXTURE_2D, texture4);
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
void divide_triangle2(point a, point b, point c, int m)
{

	/* triangle subdivision using vertex numbers
	righthand rule applied to create outward pointing faces */

	point v1, v2, v3;
	int j;
	if (m>0)
	{
		for (j = 0; j<3; j++) v1[j] = a[j] + b[j];
		//normal(v1);
		for (j = 0; j<3; j++) v2[j] = a[j] + c[j];
		//normal(v2);
		for (j = 0; j<3; j++) v3[j] = b[j] + c[j];
		//normal(v3);
		divide_triangle2(a, v1, v2, m - 1);
		divide_triangle2(c, v2, v3, m - 1);
		divide_triangle2(b, v3, v1, m - 1);
		divide_triangle2(v1, v3, v2, m - 1);
	}
	else(triangle2(a, b, c)); /* draw triangle at end of recursion */
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
	GLfloat light_position[] = {1.0, 1.0, 0.0, 0.0};
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
	//std::cout<<"请输入递归次数N>>";
	int number = (int)key;
	if(number < 48 || number > 55){
	}
	else{
		//std::cout<<number-48<<std::endl;
		n = number-48;
		display();
	}

	if(number==43){
		view_size -=0.1;
		//std::cout<<"view_size:"<<view_size<<std::endl;
	}
	else if(number == 45){
		view_size +=0.1;
		//std::cout<<"view_size:"<<view_size<<std::endl;
	}
}
