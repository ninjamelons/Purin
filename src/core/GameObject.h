#if !defined(GAME_OBJECT)
#define GAME_OBJECT

#include "Component.h"

#include <glm/glm.hpp>
#include <vector>
#include <memory>

class GameObject
{
public:
    glm::vec3 WorldPos;
    glm::vec3 RelativePos;

    glm::vec3 Orientation;

    std::vector<std::shared_ptr<Component>> Components;
    std::vector<std::shared_ptr<GameObject>> Children;

    GameObject();
    ~GameObject();
};


#endif