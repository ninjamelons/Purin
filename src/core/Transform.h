#if !defined(TRANSFORM)
#define TRANSFORM

#include "Quaternion.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform
{
public:
    glm::mat4 _worldTransform = glm::mat4(1.0f);
    glm::mat4 _localTransform = glm::mat4(1.0f);

    glm::vec3 _scale = glm::vec3(1.0f);
    glm::quat _orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 _translation = glm::vec3(0.0f);
    glm::vec3 _skew = glm::vec3(1.0f);
    glm::vec4 _perspective = glm::vec4(1.0f);

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