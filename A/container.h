
#pragma once

#include "tile.h"

class Container : public Tile
{
public:
    virtual ~Container() = default;
    virtual void update() = 0;
    virtual void add(Tile* w) = 0;
    virtual Tile* child(int i) = 0;
    //virtual void draw() = 0;
protected:
};