
#pragma once

#include "container.h"

#include <vector>

class Box : public Container
{
public:
    virtual void update() = 0;
    virtual void add(Widget* w);
    virtual Widget* child(int i);
    virtual std::string to_string();
    //virtual void draw();
protected:
    std::vector<Widget*> children;
};
