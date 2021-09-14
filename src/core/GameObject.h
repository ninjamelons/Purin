#if !defined(GAME_OBJECT)
#define GAME_OBJECT

#include "Component.h"
#include "Transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>

class GameObject
{
private:
    Transform _worldTransform;
    bool _isDirty = true;
public:
    std::string _name;
    Transform _relativeTransform;
public:
    Transform getWorldTransform();
    void setWorldTransform(const Transform& transform);

    void setParent(std::shared_ptr<GameObject> parent);

    // Gameobject members
    std::vector<std::shared_ptr<Component>> _components;
    std::vector<std::shared_ptr<GameObject>> _children;
    std::shared_ptr<GameObject> _parent;

    // Component management
    void addComponent(std::shared_ptr<Component> component);
    void removeComponent(std::string name);
    void removeAllComponents();

    // Child management
    void addChild(std::shared_ptr<GameObject> child);
    void removeChild(std::string name);
    void removeAllChildren();

    // Constructors & Destructor
    GameObject();
    GameObject(std::string name);
    GameObject(Transform relativeTransform);
    ~GameObject();
};

#endif