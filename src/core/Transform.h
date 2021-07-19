#if !defined(TRANSFORM)
#define TRANSFORM

#include "Quaternion.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform
{
public:
    glm::vec3 position;
    Quaternion rotation;
    glm::vec3 scale;

    Transform(){}
    ~Transform(){}
};


#endif