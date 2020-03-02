
#pragma once

#include "container.h"

#include <vector>

class Box : public Container
{
public:
    //virtual ~Box();
    void update();
    void add(Widget* w);
    Widget* child(int i);
protected:
    std::vector<Widget*> children;
};
