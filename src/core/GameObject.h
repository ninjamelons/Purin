#if !defined(GAME_OBJECT)
#define GAME_OBJECT

#include "Component.h"
#include "Transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <string>
#include <vector>
#include <memory>

class GameObject
{
public:
    std::string _name;

    Transform _relativeTransform;
    glm::vec4 toWorldMatrix;
    Transform _worldTransform;
    bool isDirty;

    std::vector<std::shared_ptr<Component>> _Components;
    std::vector<std::shared_ptr<GameObject>> _Children;

    std::shared_ptr<GameObject> _Parent;

    GameObject();
    GameObject(Transform relativePos);
    ~GameObject();
};

GameObject::GameObject() {}
GameObject::GameObject(Transform relativePos) {}
GameObject::~GameObject() {}

#endif