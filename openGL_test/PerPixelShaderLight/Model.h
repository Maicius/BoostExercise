#pragma once
// Std. Includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
#include "mesh.h"
#include <glm.hpp>
#include <SOIL.h>

GLint TextureFromFile(const char* path, string directory);

class Model 
{
public:
    Model(string path)
    {
        this->loadModel(path);
    }

    void Draw(Shader shader);
    
private:

    vector<Mesh> meshes;
    string directory;
    vector<Texture> textures_loaded;	

    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};
