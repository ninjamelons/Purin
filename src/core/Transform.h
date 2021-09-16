#if !defined(TRANSFORM)
#define TRANSFORM

#include "Quaternion.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

struct Translation {
    float x;
    float y;
    float z;

    glm::vec3 toVec3() const {
        return glm::vec3(x, y, z);
    }

    Translation operator+=(const Translation& other) {
        x = x + other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    Translation() { x = 0; y = 0; z = 0; }
    Translation(glm::vec3 vec) : x(vec.x), y(vec.y), z(vec.z) {}
    Translation(float x, float y, float z) : x(x), y(y), z(z) {}
};

class Transform
{
private:
    glm::mat4 _worldTransform = glm::mat4(1.0f);
    glm::mat4 _localTransform = glm::mat4(1.0f);
    glm::mat4 localTransform();
    bool _isDirty = true;
    bool _isDirtyLocal = true;
public:
    glm::mat4 worldTransform();
    void setDirty();
    void setDirtyLocal();

    glm::vec3 _scale = glm::vec3(1.0f);
    glm::quat _orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    Translation _translation = glm::vec3(0.0f);
    glm::vec3 _skew = glm::vec3(1.0f);
    glm::vec4 _perspective = glm::vec4(1.0f);

    Transform operator*(const Transform& t2);
    Transform operator+=(const Translation& t);

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