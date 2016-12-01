#version 430 core
layout(location = 0) in vec3 vPosition;
out vec4 vertexColor;
void main()
{	
    gl_Position = vec4(vPosition, 1.0);
	vertexColor = vec4(1f, 1f, 0.0f, 1.0f);
}