#include "Scene.h"

Scene::Scene() : window(nullptr), camera(new Camera(glm::vec3(0.0f, 0.0f, 3.0f)))
{
}

Scene::~Scene()
{
}