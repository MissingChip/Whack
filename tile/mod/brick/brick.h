#pragma once

#include <vector>
#include <glm/vec2.hpp>
#include "tile.h"

class Brick {
public:
    Tile* tile = nullptr;
    //Brick* parent = nullptr;
    std::vector<Brick*> bricks;
    bool forward_outclick = false;
    bool forward_outmouse = false;
    bool forward_outrelease = false;

    void attach(Tile* t);
    bool is_inside(glm::vec2 pos);
    void forward_all(bool f = true);
    virtual void update();
    //virtual void shout();
    virtual void add(Brick* p);
    virtual void insert(Brick* p, int index);
    virtual void remove(Brick* p);
    virtual void remove(uint index);
    virtual int idx_of(Brick* p);
    virtual void replace(Brick* b1, Brick* b2);
    virtual void replace(uint idx1, Brick* b2);
    virtual int interact(const glm::vec2& pos);
    virtual int check_interact(const glm::vec2& pos);

    virtual void clicked(glm::vec2 pos, int button);
    virtual void mouse(glm::vec2 pos);
    virtual void released(glm::vec2 pos, int button);
    //virtual void clicked_off(glm::vec2 pos);
    void (*on_click)(glm::vec2 pos, int button) = nullptr;
    void (*on_mouse)(glm::vec2 pos) = nullptr;
    void (*on_release)(glm::vec2 pos, int button) = nullptr;

    static const uint update_threshold = 8;
};