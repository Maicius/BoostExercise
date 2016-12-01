#include <iostream>
#include <GL/freeglut.h>

void display()
{
	glClear(GL_4D_COLOR_TEXTURE);
	glRectf(-0.3f, -0.3f, 0.6f, 0.6f);
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("test");
	glutDisplayFunc(&display);
	glutMainLoop();

	return 0;
}

