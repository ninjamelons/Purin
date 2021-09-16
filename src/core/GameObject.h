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

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
    std::string _name;
    Transform _transform;
public:
    // Gameobject members
    std::vector<std::shared_ptr<Component>> _components;
    std::vector<std::shared_ptr<GameObject>> _children;
    std::shared_ptr<GameObject> _parent;

    // Component management
    void addComponent(std::shared_ptr<Component> component);
    void removeComponent(std::string name);
    void removeAllComponents();
    template<typename T>
    std::shared_ptr<T> getComponent()
    {
        auto inContainer = std::find_if(_components.begin(), _components.end(),
            [](std::shared_ptr<Component> const& i){ return typeid(*i) == typeid(T); });
        
        if(inContainer == _components.end())
        {
            throw std::invalid_argument("Component not found");
        } else {
            return std::static_pointer_cast<T>(*inContainer);
        }
    }

    // Child management
    void addChild(std::shared_ptr<GameObject> child);
    void removeChild(std::string name);
    void removeAllChildren();

    // Constructors & Destructor
    GameObject();
    GameObject(std::string name);
    ~GameObject();
};

#endif