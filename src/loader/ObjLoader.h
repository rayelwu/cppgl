#ifndef OBJLOADER_H
#define OBJLOADER_H

#pragma once
#include <iostream>
#include <model/RawModel.h>
#include <loader/Loader.h>

class ObjLoader
{
public:
    ObjLoader();
    ~ObjLoader();

    RawModel *load(std::string fileName, Loader* loader);

private:
};

#endif