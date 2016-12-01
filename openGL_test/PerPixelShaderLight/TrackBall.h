#pragma once
#include<iostream>
#include<glm.hpp>
#include<GL/freeglut.h>
#include<gtc/matrix_transform.hpp>
#include<gtx/transform2.hpp>
#include<gtc/type_ptr.hpp>
int state=0, oldX=0, oldY=0;
float r_angle=0, dist=0;
glm::vec3 r_axis_local = glm::vec3(1.0f, 0.0f, 0.0f);;
glm::mat4 Rotate = glm::mat4(1.0f);
glm::mat4 Translate;
glm::mat4 MV, P, MVP;
glm::vec2 scaleMouse(glm::vec2 coords, glm::vec2 viewport){
	return glm::vec2( static_cast<float>(coords.x*2.f) / static_cast<float>(viewport.x) - 1.f,
                 1.f - static_cast<float>(coords.y*2.f) / static_cast<float>(viewport.y) );
}	
glm::vec3 projectToSphere(glm::vec2 xy) {
    static const float sqrt2 = sqrtf(2.f);
    glm::vec3 result;
    float d = glm::length(xy);
    float size_=2;
    if (d < size_ * sqrt2 / 2.f) {
        result.z = sqrtf(size_ * size_ - d*d);
    }
    else {
        float t = size_ / sqrt2;
        result.z = t*t / d;
    }
    result.x = xy.x;
    result.y = xy.y;
    return glm::normalize(result);
}
void SetRotateParameter(glm::vec2 newMouse,glm::vec2 oldMouse)
{
	if (newMouse == oldMouse) {
		return;
        }
    glm::vec3 p1 = projectToSphere(oldMouse);
    glm::vec3 p2 = projectToSphere(newMouse);
	glm::vec3 r_axis_world = glm::cross(p1, p2);
	glm::vec3 d = p1 - p2;
    r_angle= 180 * glm::length(d);
	
	glm::vec3 r_axis_local_end = glm::vec3(glm::inverse(MV) * glm::vec4(r_axis_world,1));
	glm::vec3 r_axis_local_start = glm::vec3(glm::inverse(MV) * glm::vec4(0.0,0.0,0.0,1));
	r_axis_local = r_axis_local_end-r_axis_local_start;
	Rotate=glm::rotate(Rotate, r_angle, r_axis_local);
}
void UpdateMatrix()
{
	Translate= glm::translate(glm::mat4(1.0f),glm::vec3(0.0f, 0.0f, dist));
	MV=Translate*Rotate;
	//get the combined modelview projection matrix
	MVP	= P*MV;
}
void OnMouseDown(int button, int s, int x, int y)
{
	
	if (s == GLUT_DOWN)
	{
		oldX = x;
		oldY = y;
	}
	if(button == GLUT_MIDDLE_BUTTON)
		state = 0;
	else
		state = 1;
}
void OnMouseMove(int x, int y)
{
	if (state == 0) {
		dist += (y - oldY)/50.0f;
	} else {
		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT,viewport);
		glm::vec2 newMouse = scaleMouse( glm::vec2(x, y), glm::vec2(viewport[2],viewport[3]));
		glm::vec2 oldMouse = scaleMouse( glm::vec2(oldX, oldY), glm::vec2(viewport[2],viewport[3]));
		SetRotateParameter(newMouse,oldMouse);
	}
	oldX = x;
	oldY = y;
	glutPostRedisplay();
}






