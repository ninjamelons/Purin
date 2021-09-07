#if !defined(RIGID_BODY)
#define RIGID_BODY

#include "Component.h"

#include <glm/glm.hpp>
#include <vector>

class RigidBody : public Component
{
public:
    RigidBody(){}
    ~RigidBody(){}
};


#endif