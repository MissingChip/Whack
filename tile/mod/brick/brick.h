#pragma once

#include <vector>
#include <glm/vec2.hpp>
#include "tile.h"

class Brick {
public:
    Tile* tile = nullptr;
    //Brick* parent = nullptr;
    std::vector<Brick*> bricks;
    void attach(Tile* t);
    virtual void update();
    //virtual void shout();
    virtual void add(Brick* p);
    virtual void insert(Brick* p, int index);
    virtual void remove(Brick* p);
    virtual int idx_of(Brick* p);
    virtual void clicked(glm::vec2 pos);
    //virtual void clicked_off(glm::vec2 pos);
    void (*on_click)(glm::vec2 pos) = nullptr;

    static const uint update_threshold = 8;
};