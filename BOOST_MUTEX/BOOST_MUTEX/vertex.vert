#version 430

layout (location = 0) in vec3 Position;
uniform mat4 MVP;
out vec3 Color;
void main()
{
    gl_Position = MVP * vec4(Position, 1.0);
	Color = clamp(Position, 0.0, 1.0);
}