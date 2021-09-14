#if !defined(RENDERER)
#define RENDERER

#include "Component.h"

class Renderer : Component
{
public:
    void Render();

    Renderer(){}
    ~Renderer(){}
};


#endif