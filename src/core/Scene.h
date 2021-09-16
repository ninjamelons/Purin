#if !defined(SCENE)
#define SCENE

#include "GameObject.h"

#include <vector>
#include <memory>

class Scene
{
public:
    std::shared_ptr<GameObject> _root;

    Scene();
    ~Scene();
};

Scene::Scene() : _root(std::make_shared<GameObject>()) {}
Scene::~Scene() {}

#endif