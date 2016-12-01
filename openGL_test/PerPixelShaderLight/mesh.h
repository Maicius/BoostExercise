#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;
#include "Shader.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    GLuint id;
    string type;
	aiString path;
};

class Mesh
{
public:
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;
    Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> texture);
	void Draw(Shader shader);
private:
    GLuint VAO, VBO, EBO;
    void setupMesh();
};