#if !defined(GAMEO_COMPONENT)
#define GAMEO_COMPONENT

#include <string>

class Component
{
protected:
    Component(){}
public:
    std::string _name;
    virtual ~Component(){}
};


#endif