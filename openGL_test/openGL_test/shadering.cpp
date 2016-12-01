/*
#include<Gl/glew.h>  
#include<gl/glxew.h>  
#include<Gl/gl.h>  
#include<GL/GLU.h>  
#include<Gl/glut.h>  
#include<stdio.h>  
#include<malloc.h>  
#include<glm.hpp>  
#include<gtc/matrix_transform.hpp>  
#include<gtx/transform.hpp>  
using  glm::vec3;  
using  glm::vec4;  
void render()  
{  
    GLenum err = glewInit();  
    if (GLEW_OK != err)  
        fprintf(stderr, "error initializaing GLew %s\n", glewGetErrorString(err));  
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);  
    const GLchar *codearray[] = {  
        "#version 430                      \n"  
        "in vec3 VertexPosition;        \n"  
        "in vec3 VertexColor;             \n"  
        "out vec3 Color ;\n"  
        " void main()                   \n"  
        "{                                \n"  
        "   Color = VertexColor;                  \n"  
        "   gl_Position = vec4(VertexPosition, 1.0);           \n"  
        "}              \n"  
  
    };  
    glShaderSource(vertShader, 1, codearray, NULL);  
    glCompileShader(vertShader);  
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);  
    const GLchar* codearray_frag[] = {  
        "#version    430                         \n"  
        "in vec3 Color;                         \n"  
        "out vec4 FragColor;                    \n"  
        "void  main()                           \n"  
        "{                                      \n"  
        "FragColor=vec4(Color,1.0);             \n"  
        "}                                      \n"  
    };  
    glShaderSource(fragShader, 1, codearray_frag, NULL);  
    glCompileShader(fragShader);  
    GLuint programHandle = glCreateProgram();  
    if (0 == programHandle)  
    {  
        fprintf(stderr, "error creating program \n");  
        exit(0);  
    }  
    glAttachShader(programHandle, vertShader);  
    glAttachShader(programHandle, fragShader);  
    glBindAttribLocation(programHandle, 0, "VertexPosition");  
    glBindAttribLocation(programHandle, 1, "VertexColor");  
    GLuint vaoHandle;  
    float positionData[] = {  
        -0.8f, -0.8f, 0.0f,  
        0.8f, -0.8f, 0.0f,  
        0.0f, 0.8f, 0.0f  
    };  
    float colorData[] = {  
        1.0f, 0.0f, 0.0f,  
        0.0f, 1.0f, 0.0f,  
        0.f, 0.0f, 1.0f  
    };  
    GLuint vboHandle[2];  
    glGenBuffers(2, vboHandle);  
    GLuint positionbufferHandle = vboHandle[0];  
    GLuint colorBufferHandle = vboHandle[1];  
    glBindBuffer(GL_ARRAY_BUFFER, positionbufferHandle);  
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positionData, GL_STATIC_DRAW);  
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);  
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colorData, GL_STATIC_DRAW);  
    glGenVertexArrays(1, &vaoHandle);  
    glBindVertexArray(vaoHandle);  
    glEnableVertexAttribArray(0);  
    glEnableVertexAttribArray(1);  
    glBindBuffer(GL_ARRAY_BUFFER, positionbufferHandle);  
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);  
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);  
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);  
    glBindVertexArray(vaoHandle);  
    //  glDrawArrays  
    glDrawArrays(GL_TRIANGLES, 0, 3);  
    glLinkProgram(programHandle);  
  
  
  
  
    GLint result;  
    glGetShaderiv(programHandle, GL_COMPILE_STATUS, &result);  
    if (GL_FALSE == result)  
    {  
        fprintf(stderr, "vertex shader compilation failed\n");  
        GLint loglen;  
        glGetProgramiv(programHandle, GL_LINK_STATUS, &loglen);  
        if (loglen > 0)  
        {  
            char*log = (char*)malloc(loglen);  
            GLsizei written;  
            glGetProgramInfoLog(programHandle, loglen, &written, log);  
            fprintf(stderr, "shader log:%s\n", log);  
            free(log);  
        }  
    }  
    else  
    {  
        ;// glUseProgram(programHandle);  
    }  
    glUseProgram(programHandle);  
    /* 
    const   GLubyte*renderer = glGetString(GL_RENDER); 
    const   GLubyte *vendor = glGetString(GL_VENDOR); 
    const   GLubyte *version = glGetString(GL_VERSION); 
    const   GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION); 
    GLint major, minor; 
    glGetIntegerv(GL_MAJOR_VERSION, &major); 
    glGetIntegerv(GL_MINOR_VERSION, &minor); 
    printf("GL vendor:%s\n", vendor); 
    printf("GL renderer:%s\n", renderer); 
    printf("GL version(s):%s\n", version); 
    printf("GL version(d):%d,%d\n", major,minor); 
    printf("GL version:%s\n", glslVersion); 
 
  
    ;  
  
  
}  
int main(int argc, char**argv)  
{  
  
    glutInit(&argc, argv);  
  
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);  
    glutCreateWindow("ss");  
      
    glutDisplayFunc(render);  
  
    glutMainLoop();  
    return 0;  
    //vec3 VertexPosition = vec3(1, 0,  1.0f);  
    //vec3 VertexColor = vec3(1.0f, 0, 0)   ;  
  
  
  
    //return 0;  
}  */