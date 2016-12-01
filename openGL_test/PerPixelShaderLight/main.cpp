//#include <iostream>
//#include <math.h>
//#include <GL/glew.h>
//#include <GL/freeglut.h>
//#include "TrackBall.h"
//#include "mesh.h"
//#include "Shader.h"
//#include "Model.h"
//using namespace std;
//
//GLuint VBO, IBO;
//GLint MVPLocation;
//GLint WorldLocation;
//GLuint FBO, TextureName, DBO;
//static float mouseX = -1.0f,mouseY = -1.0f;
//static float moveX= 0.0f, moveY = 0.0f;
//class Vector3f{
//private:
//	float x, y, z;
//public:
//	Vector3f(){};
//	Vector3f(float x, float y, float z){
//		this->x = x;
//		this->y = y;
//		this->z = z;
//	}
//};
////static void RenderSceneCB()
////
////{
////	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, FBO);
////	glPushAttrib(GL_VIEWPORT_BIT);
////	glViewport(0, 0, 1080, 720);
////
////	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
////	glEnable(GL_TEXTURE_2D);
////	glBindTexture(GL_TEXTURE_2D, TextureName);
////	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
////
////	UpdateMatrix();
////	glUniformMatrix4fv(MVPLocation, 1, GL_TRUE, value_ptr(MVP));
////	glEnableVertexAttribArray(0);
////	glBindBuffer(GL_ARRAY_BUFFER, VBO);
////	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
////	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
////
////	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
////	glEnable(GL_TEXTURE_2D);
////	glBindTexture(GL_TEXTURE_2D, TextureName);
////	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
////	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
////	glDisableVertexAttribArray(0); 
////
////    glutSwapBuffers();
////}
//
////static void InitializeGlutCallbacks()
////{
////    glutDisplayFunc(RenderSceneCB);
////    glutIdleFunc(RenderSceneCB);
////}
//////
////static void CreateVertexBuffer(){
////	Vector3f Vertices[8];
////	Vertices[0] = Vector3f(-0.6f, -0.6f, 0.0f);
////	Vertices[1] = Vector3f(0.0f, -0.6f, 0.6f);
////	Vertices[2] = Vector3f(0.6f, -0.6f, 0.0f);
////	Vertices[3] = Vector3f(0.0f, 0.6f, 0.0f);
////
////	glGenBuffers(1, &VBO);
////	glBindBuffer(GL_ARRAY_BUFFER, VBO);
////	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
////}
////
////static void CreateIndexBuffer()
////{
////    unsigned int Indices[] = { 0, 3, 1,
////        1, 3, 2,
////        2, 3, 0,
////        0, 1, 2 };
////
////    glGenBuffers(1, &IBO);
////    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
////    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
////}
//
//
////static void CompileShaders()
////{
////	Shader shader("vertex.vert", "fragment.frag");
////	shader.Use();
////	MVPLocation = glGetUniformLocation(shader.Program, "MVP");
////}
////void initFBO(){
////	glGenFramebuffersEXT(1, &FBO);
////	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, FBO);
////
////	glGenTextures(1, &TextureName);
////	glBindTexture(GL_TEXTURE_2D, TextureName);
////
////	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
////	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
////
////	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
////
////	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, TextureName, 0);
////	glGenRenderbuffersEXT(1, &DBO);
////	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, DBO);
////	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, 256, 256);
////	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, DBO);
////
////
////	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
////	switch( status){
////	case GL_FRAMEBUFFER_COMPLETE_EXT:
////		cout<<"FBO IS COMPLETED!"<<endl;
////		break;
////	case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
////		MessageBox(NULL, "GL_FRAMBUFFER_UNSUPPORTED_EXT!","ERROR", MB_OK | MB_ICONEXCLAMATION);
////		exit(0);
////		break;
////	}
////}
//int main(int argc, char* argv[])
//{
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
//    glutInitWindowSize(1080, 720);
//    glutInitWindowPosition(100, 100);
//    glutCreateWindow("PER PIXEL SHADERING");
//	//InitializeGlutCallbacks();
//	
//	glewExperimental = GL_TRUE;
//	if (glewInit()) {
//		cerr <<"Unable to initialize GLEW ... exiting"<<endl;
//		exit(EXIT_FAILURE);
//	}
//	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
//	glEnable(GL_DEPTH_TEST);
//	
//	Model model("E:/AAÊµÑéÊÒ/nanosuit/nanosuit.obj");
//	Shader shader("vertex.vert", "fragment.frag");
//	shader.Use();
//	glutMouseFunc(OnMouseDown);
//	glutMotionFunc(OnMouseMove);
//	glutDisplayFunc();
//	UpdateMatrix();
//	MVPLocation = glGetUniformLocation(shader.Program, "MVP");
//	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, value_ptr(MVP));
//	//initFBO();
//	//CreateVertexBuffer();
//	//CreateIndexBuffer();
//	
//	//CompileShaders();
//    glutMainLoop();
//
//    return 0;
//}