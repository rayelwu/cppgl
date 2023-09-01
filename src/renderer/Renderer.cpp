#include "Renderer.h"
#include <iostream>

Renderer::Renderer(Shader *shader)
{
    this->shader = shader;
}

Renderer::~Renderer()
{
}

void Renderer::render(RawModel *model)
{
    //std::cout << "Use Vao: " << model->vao << ", vertextCount: " << model->vertexCount << std::endl;
    glBindVertexArray(model->vao);
    this->shader->Use();
    //glDrawArrays(GL_TRIANGLES, 0, model->vertexCount);
    glDrawElements(GL_TRIANGLES, model->vertexCount, GL_UNSIGNED_INT, 0);
}

void Renderer::clear()
{
    // 渲染
    // 清楚颜色缓冲
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
