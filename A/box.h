
#pragma once

#include "container.h"

#include <vector>

class Box : public Container
{
public:
    virtual void update() = 0;
    virtual void add(Tile* w);
    virtual Tile* child(int i);
    
protected:
    std::vector<Tile*> children;
};
