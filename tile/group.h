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
    Group(float w, float h);
    virtual ~Group();
    virtual void update();
    virtual void update_all();
    virtual void shout();
    virtual void add(Tile* t);
    virtual void add(Modifier* m);
    virtual void insert(Modifier* m, int index);
    virtual void insert(Tile* t, int index);
    virtual void remove(Tile* t);
    virtual void remove(Modifier* m);
    virtual int idx_of(Tile* t);
    virtual int idx_of(Modifier* t);
    virtual void replace(Tile* t1, Tile* t2);
};

inline Group::Group(Tile* t){
    add(t);
    size = t->size;
}

inline Group::Group(float w, float h){
    size.x = w;
    size.y = h;
}