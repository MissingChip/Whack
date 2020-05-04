#pragma once

#include <cstdio>
#include <vector>

#include "tile.h"
#include "group.h"

class Modifier {
public:

    virtual void apply(Group*) = 0;
    virtual void update(){};
};