#pragma once

#include <vector>
#include <glm/vec2.hpp>
#include "tile.h"

class Page {
public:
    Tile* tile;
    //vector<
    virtual void clicked_off(glm::vec2 pos);
    virtual Page* clicked(glm::vec2 pos);
    void (*on_clicked)(glm::vec2 pos);
};