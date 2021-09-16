#include "GameObject.h"

// Component management
void GameObject::addComponent(std::shared_ptr<Component> component)
{
    auto inContainer = std::find_if(_components.begin(), _components.end(), 
        [component](std::shared_ptr<Component> const& i){ return i.get() == component.get(); });
    
    if(inContainer == _components.end())
    {
        _components.push_back(component);
    } else {
        throw std::invalid_argument("Component already added");
    }
}
void GameObject::removeComponent(std::string name)
{
    auto inContainer = std::remove_if(_components.begin(), _components.end(),
        [name](std::shared_ptr<Component> const& i){ return i->_name == name; });
    
    if(inContainer == _components.end())
    {
        throw std::invalid_argument("Component not found");
    }
}
void GameObject::removeAllComponents()
{
    _components.clear();
}

// Child management
void GameObject::addChild(std::shared_ptr<GameObject> child)
{
    auto inContainer = std::find_if(_children.begin(), _children.end(), 
        [child](std::shared_ptr<GameObject> const& i){ return i.get() == child.get(); });
    
    if(inContainer == _children.end())
    {
        _children.push_back(child);
        child->_parent = this->shared_from_this();
    } else {
        throw std::invalid_argument("Child already added");
    }
}
void GameObject::removeChild(std::string name)
{
    auto inContainer = std::remove_if(_children.begin(), _children.end(), 
        [name](std::shared_ptr<GameObject> const& i){ return i->_name == name; });
    
    if(inContainer == _children.end())
    {
        throw std::invalid_argument("Child not found");
    }
}
void GameObject::removeAllChildren()
{
    _children.clear();
}

// Constructors & Destructor
GameObject::GameObject() : _parent(nullptr) {}
GameObject::GameObject(std::string name) : _name(name) {}
GameObject::~GameObject() {}