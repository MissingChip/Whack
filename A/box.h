#pragma once
#include <vector>

#include "tile.h"
class Box : public Tile {
private:

public:
    std::vector<Tile*> childs;

    Box();
    virtual ~Box();
};

Box::Box(){};
Box::~Box(){};