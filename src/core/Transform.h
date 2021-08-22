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

    Transform() :
        _scale(1.0f),
        _orientation(1.0f, 0.0f, 0.0f, 0.0f),
        _translation(0.0f, 0.0f, 0.0f) {}
    Transform(const Transform& t) :
        _scale(t._scale),
        _orientation(t._orientation),
        _translation(t._translation),
        _skew(t._skew),
        _perspective(t._perspective) {}
    Transform(const glm::vec3& scale, const glm::quat& orientation,
        const glm::vec3& translation, const glm::vec3& skew,
        const glm::vec4& perspective) :
            _scale(scale),
            _orientation(orientation),
            _translation(translation),
            _skew(skew),
            _perspective(perspective) {}
    Transform(const glm::vec3& scale, const glm::quat& orientation,
        const glm::vec3& translation) :
            _scale(scale),
            _orientation(orientation),
            _translation(translation) {}
    
    ~Transform(){}

    Transform operator*(const Transform& t2)
    {
        Transform t1(*this);
        glm::mat4 translate = glm::translate(glm::mat4(1.0), _translation);
        glm::mat4 rotate = glm::mat4_cast(_orientation);
        glm::mat4 scale = glm::scale(glm::mat4(1.0), _scale);

        _localTransform = translate * rotate * scale;

        t1._worldTransform = _localTransform * t2._worldTransform;

        return t1;
    }
};


#endif