#if !defined(RENDERER)
#define RENDERER

#include "Component.h"
#include "Transform.h"

class Renderer : Component
{
public:
    void render(Transform world);

    Renderer(){}
    ~Renderer(){}
};


#endif