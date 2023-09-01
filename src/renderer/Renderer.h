#ifndef RENDERER_H
#define RENDERER_H

#pragma once

#include "model/RawModel.h"
#include "shader/Shader.h"

class Renderer
{
public:
    Shader* shader;
    Renderer(Shader *);
    ~Renderer();
    void render(RawModel *model);
    void clear();

private:
};

#endif