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
    bool _isDirty;
public:
    std::string _name;
    Transform _relativeTransform;
public:
    Transform getWorldTransform();
    void setWorldTransform(const Transform& transform);

    void setParent(std::shared_ptr<GameObject> parent);

    // Gameobject members
    std::vector<std::shared_ptr<Component>> _Components;
    std::vector<std::shared_ptr<GameObject>> _Children;
    std::shared_ptr<GameObject> _Parent;

    // Component management
    void addComponent(std::shared_ptr<Component> component);
    void removeComponent(std::string name);
    void removeAllComponents();

    // Child management
    void addChild(std::shared_ptr<GameObject> child);
    void removeChild(std::string name);
    void removeAllChildren();

    // Constructors & Destructor
    GameObject::GameObject(std::string name);
    GameObject(Transform relativeTransform);
    ~GameObject();
};

Transform GameObject::getWorldTransform()
{
    if(_isDirty)
        _worldTransform = _worldTransform * _Parent->_worldTransform;
        _isDirty = false;
    return _worldTransform;
}

void GameObject::setWorldTransform(const Transform& transform)
{
    _worldTransform = transform;
    _isDirty = true;
}

// Child management
void GameObject::addChild(std::shared_ptr<GameObject> child)
{
    auto inContainer = std::find_if(_Children.begin(), _Children.end(), 
        [child](std::shared_ptr<GameObject> const& i){ return i.get() == child.get(); });
    
    if(inContainer == _Children.end())
    {
        _Children.push_back(child);
    } else {
        throw std::invalid_argument("Child already added");
    }
}
void GameObject::removeChild(std::string name)
{
    auto inContainer = std::remove_if(_Children.begin(), _Children.end(), 
        [name](std::shared_ptr<GameObject> const& i){ return i->_name == name; });
    
    if(inContainer == _Children.end())
    {
        throw std::invalid_argument("Child not found");
    }
}
void GameObject::removeAllChildren()
{
    _Children.clear();
}

// Component management
void GameObject::addComponent(std::shared_ptr<Component> component)
{
    auto inContainer = std::find_if(_Components.begin(), _Components.end(), 
        [component](std::shared_ptr<Component> const& i){ return i.get() == component.get(); });
    
    if(inContainer == _Components.end())
    {
        _Components.push_back(component);
    } else {
        throw std::invalid_argument("Component already added");
    }
}
void GameObject::removeComponent(std::string name)
{
    auto inContainer = std::remove_if(_Components.begin(), _Components.end(),
        [name](std::shared_ptr<Component> const& i){ return i->_name == name; });
    
    if(inContainer == _Components.end())
    {
        throw std::invalid_argument("Component not found");
    }
}
void GameObject::removeAllComponents()
{
    _Components.clear();
}

// Constructors & Destructor
GameObject::GameObject(std::string name) : _name(name) {}
GameObject::GameObject(Transform relativeTransform) : _relativeTransform(relativeTransform) {}
GameObject::~GameObject() {}

#endif