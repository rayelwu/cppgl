#include "ObjLoader.h"
#include <fstream>
#include <iostream>

ObjLoader::ObjLoader()
{
}

ObjLoader::~ObjLoader()
{
}

RawModel *ObjLoader::load(std::string fileName, Loader *loader)
{
    std::ifstream objFile;
    std::vector<float> vertices;
    std::vector<float> textures;
    std::vector<float> normals;
    std::vector<float> indices;

    objFile.exceptions(std::ifstream::badbit);
    try
    {
        objFile.open(fileName);
        std::string line;
        // TODO
        // while (std::getline(objFile, line))
        // {
            
        //     std::cout << line << std::endl;
        // }
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::OBJ_LOADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    return nullptr;
}
