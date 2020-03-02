
#pragma once

#include "widget.h"

class Container : public Widget
{
public:
    virtual ~Container() = default;
    virtual void update() = 0;
    virtual void add(Widget* w) = 0;
    virtual Widget* child(int i) = 0;
    virtual std::string to_string() = 0;
    //virtual void draw() = 0;
protected:
};