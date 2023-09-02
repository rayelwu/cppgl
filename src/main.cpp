#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <cmath>
#include <shader/Shader.h>
#include <loader/Loader.h>
#include <renderer/Renderer.h>
#include <model/RawModel.h>
#include <app/App.h>
#include <window/Window.h>
#include <scene/Scene.h>

class GLScene : public Scene
{

public:
    Loader loader;
    Shader *shader;
    Renderer *renderer;
    RawModel *model;

    float transX, transY, transZ;
    float rotateX, rotateY, rotateZ;
    float scaleX, scaleY, scaleZ;

    GLScene()
    {
        this->shader = new Shader("../res/vertex.glsl", "../res/fragment.glsl");
        this->renderer = new Renderer(this->shader);
        // 设置顶点
        float postions[] = {
            0.5f,
            -0.5f,
            0.0f,
            -0.5f,
            -0.5f,
            0.0f,
            -0.5f,
            0.5f,
            0.0f,
            0.5f,
            0.5f,
            0.0f,
        };
        float colours[] = {
            1.0f,
            0.0f,
            0.0f,
            0.0f,
            1.0f,
            0.0f,
            0.0f,
            0.0f,
            1.0f,
            1.0f,
            0.0f,
            0.0f,
        };
        int indices[] = {0, 1, 2, 3, 0, 2};
        this->model = this->loader.load(postions, colours, indices);
        this->transX = 0;
        this->transY = 0;
        this->transZ = 0;

        this->rotateX = 0;
        this->rotateY = 0;
        this->rotateZ = 0;

        this->scaleX = 1.0f;
        this->scaleY = 1.0f;
        this->scaleZ = 1.0f;
    }

    glm::mat4 calculateTransform()
    {
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(transX, transY, transZ));
        trans = glm::rotate(trans, rotateX, glm::vec3(1.0f, 0.0f, 0.0f));
        trans = glm::rotate(trans, rotateY, glm::vec3(0.0f, 1.0f, 0.0f));
        trans = glm::rotate(trans, rotateZ, glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::scale(trans, glm::vec3(scaleX, scaleY, scaleZ));
        return trans;
    }

    virtual void render() override
    {
        this->renderer->clear();
        if (this->shader)
        {
            this->shader->Use();
        }
        this->shader->setUniform1f("aAplha", sin(glfwGetTime()) / 2.0f + 0.5f);
        this->shader->setUniformMatrix4fv("transform", this->calculateTransform());
        this->renderer->render(this->model);
    }

    void onMouseEvent(MouseEvent *event) override
    {
        this->transX = event->worldX;
        this->transY = event->worldY;
        this->rotateZ = (float)glfwGetTime();
        this->scaleX = std::abs(std::sin(glm::radians((float)glfwGetTime() * 100)));
        this->scaleY = std::abs(std::sin(glm::radians((float)glfwGetTime() * 100)));
        this->scaleZ = std::abs(std::sin(glm::radians((float)glfwGetTime() * 100)));
    }
};

int main()
{
    App app;
    app.createWindow("CppGL", 800, 600)->addScene("default", new GLScene());
    app.loop();
    app.exit();
    return 0;
}