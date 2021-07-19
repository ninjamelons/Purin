#if !defined(SCENE)
#define SCENE

#include "GameObject.h"

#include <vector>
#include <memory>

class Scene
{
public:
    GameObject root;
    std::vector<std::shared_ptr<GameObject>> gameObjects;

    Scene();
    ~Scene();
};

Scene::Scene() {}
Scene::~Scene() {}

#endif