#pragma once

#include <vector>

#include "tile.h"
class Modifier;

class Group : public Tile {
public:
    std::vector<Tile*> in;
    std::vector<Modifier*> mods;

    Group(){};
    Group(Tile* t);
    virtual ~Group();
    virtual void update();
    virtual void update_all();
    virtual void add(Tile* t);
    virtual void add(Modifier* m);
};

inline Group::Group(Tile* t){
    add(t);
    size = t->size;
}