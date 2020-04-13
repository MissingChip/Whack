#pragma once

#include <vector>

#include "tile.h"

class Modifier;

class Group : public Tile {
public:
    std::vector<Tile*> in;
    std::vector<Modifier*> mods;

    virtual void update();
    virtual void update_all();
};

inline void Group::update() {
    for(Modifier* m : mods){
        m->apply(this);
    }
}