#include <GL/freeglut.h>  
#include <iostream>
#include <glm.hpp>
using namespace std;
#define draw_point 1
#define draw_line 2
#define draw_triangle 3
GLint nSelected = draw_triangle;

int n = 5;
const int width = 1280;
const int height = 720;
glm::vec2 Left = glm::vec2(-0.6f, -0.6f);
glm::vec2 Right = glm::vec2(0.6f, -0.6f);
glm::vec2 Top = glm::vec2(0.f, 0.6f);
glm::mat3x2 point = glm::mat3x2(Left, Right, Top);
int oldX = 0, oldY = 0;
GLfloat mouseX = 0, mouseY = 0;

//*************************************
//稳定图形形状
void reshape(GLsizei w,GLsizei h)
{
	GLfloat ratio=(GLfloat)w/(GLfloat)h;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w <= h)
		gluOrtho2D(-1.0,1.0,-1.0/ratio,1.0/ratio);
	else
		gluOrtho2D(-1.0*ratio,1.0*ratio,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//*************************************
//将鼠标坐标映射到0-1范围内且以画面中心为原点的坐标
glm::vec2 scaleMouse(glm::vec2 coords, glm::vec2 viewport){
	return glm::vec2( static_cast<float>(coords.x*2.f) / static_cast<float>(viewport.x) - 1.f,
                 1.f - static_cast<float>(coords.y*2.f) / static_cast<float>(viewport.y) );
}
void OnMouseDown(int button, int state, int x, int y)
{	
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){
			oldX = x;
			oldY = y;
	}
}

//*************************************
//计算三角形面积，用以判断点是否在三角形内
//当鼠标的点与三个顶点形成的三角形总面积等于三角形面积时
//该点在三角形内部
float area(glm::vec2 a,glm::vec2 b,glm::vec2 c){
	return 
		std::abs(a.x*b.y + b.x*c.y + c.x * a.x - a.y* b.x - b.y*c.x - c.y*a.x)/2.0f;//判断一个点在三角形内
}

//*************************************
//鼠标移动，判断鼠标点在三角形内，并拖动
void OnMouseMove(int x, int y)
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT,viewport);
	glm::vec2 newMouse = scaleMouse( glm::vec2(x, y), glm::vec2(viewport[2],viewport[3]));
	glm::vec2 oldMouse = scaleMouse( glm::vec2(oldX, oldY), glm::vec2(viewport[2],viewport[3]));
	
	float s1 = area(newMouse, Left, Right);
	float s2 = area(newMouse, Left, Top);
	float s3 = area(newMouse, Top, Right);
	float s = area(Left, Top, Right);;

	if(s1 + s2 + s3 - s < 0.1f){
		mouseX = newMouse.x - oldMouse.x;
		mouseY = newMouse.y - oldMouse.y;

		Left.x +=mouseX;
		Left.y +=mouseY;
		Right.x +=mouseX;		
		Right.y +=mouseY;		
		Top.x +=mouseX;
		Top.y +=mouseY;
	}
	else {
		mouseX = 0;
		mouseY = 0;
	}
	oldX = x;
	oldY = y;
	glutPostRedisplay();
}

//*************************************
//菜单选择
void OnMenu(int value)
{
	nSelected = value;
	glutPostRedisplay();
}

//*************************************
//创建菜单
void createMenu()
{
	glutAddMenuEntry("Point Primitive", draw_point); //增加菜单
	glutAddMenuEntry("Line Primitive", draw_line);
	glutAddMenuEntry("Triangle Primitive", draw_triangle);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//*************************************
//画三角形
void triangle(glm::vec2 a, glm::vec2 b, glm::vec2 c)
{
	a[0] +=mouseX;
	a[1] +=mouseY;
	b[0] +=mouseX;
	b[1] +=mouseY;
	c[0] +=mouseX;
	c[1] +=mouseY;

	glVertex2f(a.x, a.y);
	glVertex2f(b.x, b.y);
	glVertex2f(c.x, c.y);

}

//*************************************
//判断键盘按键，如果为Q则退出
void pressKeys(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q') {
		exit(0);
	}
}

//*************************************
//线面元下画三角形
void triangle_LINE(glm::vec2 a, glm::vec2 b, glm::vec2 c)
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(a.x, a.y);
	glVertex2f(b.x, b.y);
	glVertex2f(c.x, c.y);
	glEnd();
	glFlush();
}

////*************************************
//递归画三角形
void triangle_iteration(glm::vec2 a, glm::vec2 b, glm::vec2 c, int n, int select)
{
	glm::vec2 v1, v2, v3;//0号位置放x点，1号位置放y点

	if(n > 0)
	{
		//新得顶点移动到上一次得线中点
		for (int i = 0; i < 2; i++) {
			v1[i] = (a[i] + b[i]) / 2;
		}
		for (int j = 0; j < 2; j++) {
			v2[j] = (a[j] + c[j]) / 2;
		}
		for (int k = 0; k < 2; k++) {
			v3[k] = (b[k] + c[k]) / 2;
		}
		triangle_iteration(a, v2, v1, n - 1, select);
		triangle_iteration(b, v3, v1, n - 1, select);
		triangle_iteration(c, v2, v3, n - 1, select);
	}
	else
	{
		triangle(a,b,c);
	}
	if(select == draw_line)
	{
		triangle_LINE(a, b, c);
	}
}

//*************************************
//渲染函数
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	switch (nSelected)
	{
	case(draw_point):
		glBegin(GL_POINTS);
		break;
	case(draw_line):
		glBegin(GL_LINES);
		break;
	case(draw_triangle):
		glBegin(GL_TRIANGLES);
		break;
	default:
		break;
	}
	triangle_iteration(Left, Right, Top,n, nSelected);
	glEnd();
	glFlush();

}
void init()
{
	glClearColor (0.0, 0.0, 0.0, 0.0); //设置背景颜色为黑色；red green blue alpha
	glColor3f(1.0, 1.0, 1.0); //设置第一个顶点为红色
	glMatrixMode (GL_PROJECTION);//投影 ；GL_PROJECTION是对投影矩阵操作，GL_MODELVIEW是对模型视景矩阵操作，GL_TEXTURE是对纹理矩阵进行随后的操作
	glLoadIdentity (); //重置当前指定的矩阵为单位矩阵
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); //截取函数
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);							//初始化glut库
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);	// 设置初始显示模式，RGB颜色模式窗口
	glutInitWindowSize(width,height);					//窗口得大小
	glutInitWindowPosition(100,100);				//传入x,y ;x是窗口距离屏幕左边得距离 y是窗口距离屏幕上边得距离
	glutCreateWindow("Triangle");						//创建窗口，命名三角形
	glutMouseFunc(OnMouseDown);
	glutMotionFunc(OnMouseMove);
	glutKeyboardFunc(pressKeys);
	glutCreateMenu(OnMenu);
	glutDisplayFunc(display);						//对窗体进行重新绘制
	glutReshapeFunc(reshape);
	createMenu();
	init();
	glutMainLoop();									//进入jlut事件处理循环		

}

