#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <cmath>
#include <shader/Shader.h>
#include <loader/Loader.h>
#include <loader/ObjLoader.h>
#include <renderer/Renderer.h>
#include <model/RawModel.h>
#include <app/App.h>
#include <window/Window.h>
#include <scene/Scene.h>
#include <camera/Camera.h>

class GLScene : public Scene
{
private:
    float transX, transY, transZ;
    float rotateX, rotateY, rotateZ;
    float scaleX, scaleY, scaleZ;

    Loader loader;
    Shader *shader;
    Renderer *renderer;
    RawModel *model;
    glm::vec3 lightPos;
    glm::mat4 world;

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

    glm::mat4 calculatePerspective()
    {
        return glm::perspective(glm::radians(45.0f), (float)this->window->width / (float)this->window->height, 0.1f, 100.0f);
    }

    RawModel *loadPlaneModel()
    {
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
        return this->loader.load(postions, 4, colours, 4, indices, 6);
    }

    RawModel *loadCubeModel()
    {
        auto pos = std::vector<float>{
            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            -0.5f, 0.5f, -0.5f};

        auto colours = std::vector<float>{
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

        auto indices = std::vector<int>{
            // 0123
            0,
            1,
            2,
            3,
            0,
            2,
            // 4567
            4,
            5,
            6,
            7,
            4,
            6,

            // 1562
            1,
            5,
            6,
            2,
            1,
            6,
            // 0473
            0,
            4,
            7,
            3,
            0,
            7,
            // 0451
            0,
            4,
            5,
            1,
            0,
            5,
            // 3267
            3,
            2,
            6,
            7,
            3,
            6,
        };
        //ObjLoader ObjLoader;
        //ObjLoader.load("../res/dragon.obj", &this->loader);
        return this->loader.load(pos, colours, indices);
    }

public:
    GLScene()
    {
        shader = new Shader("../res/vertex.glsl", "../res/fragment.glsl");
        renderer = new Renderer(this->shader);

        transX = 0;
        transY = 0;
        transZ = 0;

        rotateX = 0;
        rotateY = 0;
        rotateZ = 0;

        scaleX = 1.0f;
        scaleY = 1.0f;
        scaleZ = 1.0f;

        model = loadCubeModel();
        lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
        world = glm::mat4(1.0f);
    }

    virtual void render() override
    {
        renderer->clear();
        if (shader)
        {
            shader->Use();
        }
        shader->setUniform1f("alpha", sin(glfwGetTime()) / 2.0f + 0.5f);
        shader->setUniformMatrix4fv("world", world);
        shader->setUniformMatrix4fv("view", camera->GetViewMatrix());
        shader->setUniformMatrix4fv("projection", this->calculatePerspective());
        shader->setUniform3f("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
        shader->setUniform3f("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setUniform3f("lightPos", lightPos);
        renderer->render(this->model);
    }

    void onMouseEvent(MouseEvent *event) override
    {
        transX = event->worldX;
        transY = event->worldY;
        transZ = -3.0f;
        rotateZ = (float)glfwGetTime();
        scaleX = std::abs(std::sin(glm::radians((float)glfwGetTime() * 100)));
        scaleY = std::abs(std::sin(glm::radians((float)glfwGetTime() * 100)));
        scaleZ = std::abs(std::sin(glm::radians((float)glfwGetTime() * 100)));
    };
};

int main()
{
    App app;
    app.createWindow("CppGL", 800, 600)->addScene("default", new GLScene());
    app.loop();


    return app.exit();
}