#pragma once

#include <vector>
#include <glm/vec2.hpp>
#include "tile.h"

class Coat {
public:
    Tile* tile;
    std::vector<Coat*> pages;
    void attach(Tile* t);
    virtual void update();
    virtual void add(Coat* p);
    virtual void insert(Coat* p, int index);
    virtual void remove(Coat* p);
    virtual int idx_of(Coat* p);
    virtual void clicked(glm::vec2 pos);
    //virtual void clicked_off(glm::vec2 pos);
    void (*on_click)(glm::vec2 pos) = nullptr;

    static const uint update_threshold = 8;
};