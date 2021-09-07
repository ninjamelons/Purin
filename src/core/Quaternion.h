#if !defined(QUATERNION)
#define QUATERNION

#include <glm/glm.hpp>

class Quaternion
{
public:
    float x;
    float y;
    float z;
    float w;

    glm::vec3 getEuler();

    Quaternion();
    ~Quaternion();
};


#endif