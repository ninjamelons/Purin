#if !defined(TRANSFORM)
#define TRANSFORM

#include "Quaternion.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform
{
public:
    glm::mat4 _worldTransform;
    glm::mat4 _localTransform;

    glm::vec3 _scale;
    glm::quat _orientation;
    glm::vec3 _translation;
    glm::vec3 _skew;
    glm::vec4 _perspective;

    Transform operator*(const Transform& t2);

    ~Transform();
    Transform();
    Transform(const Transform& t);
    Transform(const glm::vec3& scale,
        const glm::quat& orientation,
        const glm::vec3& translation,
        const glm::vec3& skew,
        const glm::vec4& perspective);
    Transform(const glm::vec3& scale,
        const glm::quat& orientation,
        const glm::vec3& translation);
};


#endif