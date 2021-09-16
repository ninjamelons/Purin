#include "Transform.h"

glm::mat4 Transform::worldTransform() {
    auto local = localTransform();

    if(_isDirty) {
        _worldTransform = local; // TODO - Temporary - Need to multiply by parent transform
        _isDirty = false;
    }
    return _worldTransform;
}

glm::mat4 Transform::localTransform() {
    if(_isDirtyLocal) {
        _localTransform = glm::mat4(1.0f);
        _localTransform = glm::translate(_localTransform, _translation.toVec3());
        _localTransform *= glm::mat4_cast(_orientation);
        _localTransform = glm::scale(_localTransform, _scale);
        _isDirtyLocal = false;
    }
    return _localTransform;
}

void Transform::setDirty() {
    _isDirty = true;
    _isDirtyLocal = true;
}

void Transform::setDirtyLocal() {
    _isDirtyLocal = true;
}

Transform Transform::operator*(const Transform& t2)
{
    Transform t1(*this);
    glm::mat4 translate = glm::translate(glm::mat4(1.0), _translation.toVec3());
    glm::mat4 rotate = glm::mat4_cast(_orientation);
    glm::mat4 scale = glm::scale(glm::mat4(1.0), _scale);

    _localTransform = translate * rotate * scale;

    t1._worldTransform = _localTransform * t2._worldTransform;

    return t1;
}

Transform Transform::operator+=(const Translation& trans)
{
    _translation += trans;
    _isDirty = true;
    _isDirtyLocal = true;
    return *this;
}

Transform::Transform() :
    _scale(glm::vec3(1.0f)),
    _orientation(1.0f, 0.0f, 0.0f, 0.0f),
    _translation(0.0f, 0.0f, 0.0f) {}
Transform::Transform(const Transform& t) :
    _scale(t._scale),
    _orientation(t._orientation),
    _translation(t._translation),
    _skew(t._skew),
    _perspective(t._perspective) {}
Transform::Transform(const glm::vec3& scale,
    const glm::quat& orientation,
    const glm::vec3& translation,
    const glm::vec3& skew,
    const glm::vec4& perspective) :
        _scale(scale),
        _orientation(orientation),
        _translation(translation),
        _skew(skew),
        _perspective(perspective) {}
Transform::Transform(const glm::vec3& scale,
    const glm::quat& orientation,
    const glm::vec3& translation) :
        _scale(scale),
        _orientation(orientation),
        _translation(translation) {}

Transform::~Transform() {}