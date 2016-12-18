#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/freeglut.h>
class Shader
{
public:
    GLuint Program;
    Shader(GLchar* vertexPath, GLchar* fragmentPath);
    void Use();
private:
	void  Shader::AddShader(GLuint ShaderProgram, const GLchar* pShaderText, 
		GLenum ShaderType);
	GLchar* readFile(char* filename );
};
#endif