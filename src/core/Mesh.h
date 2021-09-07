#if !defined(OBJECT_MESH)
#define OBJECT_MESH

#include "Component.h"

class Mesh : public Component
{
public:
    float *_vertices;

    Mesh() {}
    ~Mesh(){}
};


#endif