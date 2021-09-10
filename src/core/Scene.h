#if !defined(SCENE)
#define SCENE

#include "GameObject.h"

#include <vector>
#include <memory>

class Scene
{
public:
    GameObject _root;

    Scene();
    ~Scene();
};

Scene::Scene() {}
Scene::~Scene() {}

#endif