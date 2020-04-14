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
    void add(Tile* t);
    void add(Modifier* m);
};

inline void Group::add(Tile* t){
    in.push_back(t);
}
inline void Group::add(Modifier* m){
    mods.push_back(m);
}