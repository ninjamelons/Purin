#include "GameObject.h"

Transform GameObject::getWorldTransform()
{
    if(_isDirty)
        _worldTransform = _Parent->_worldTransform * _worldTransform;
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
GameObject::GameObject() : _Parent(nullptr), _isDirty(true) {}
GameObject::GameObject(std::string name) : _name(name) {}
GameObject::GameObject(Transform relativeTransform) : _relativeTransform(relativeTransform) {}
GameObject::~GameObject() {}