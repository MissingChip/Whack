#pragma once

#include <vector>

#include "tile.h"
#include "group.h"

class Modifier {
public:
    std::vector<Group*> groups;

    virtual void apply(Group*) = 0;
    virtual void update();
};

inline void Modifier::update() {
    for(Group* g : groups){
        apply(g);
    }
}