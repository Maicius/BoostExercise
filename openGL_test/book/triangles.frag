#version 430 core
uniform vec4 ourColor;
out vec4 fColor;
void
main()
{
    fColor = ourColor;
}