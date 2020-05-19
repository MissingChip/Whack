#pragma once

#include "brick.h"

class Fold : public Brick {
public:
    Fold();
    virtual ~Fold();

    int drag = 0;
    int dir = -1;
    bool created;
    glm::vec2 trigger = glm::vec2(24, 24);
    glm::vec2 trigger_pos;
    glm::vec2 anchor_pos;
    glm::vec2 psize;
    virtual void update();
    virtual void clicked(glm::vec2 pos, int button);
    virtual void mouse(glm::vec2 pos);
    virtual void released(glm::vec2 pos, int button);

    Brick* new_empty();
    bool dir_unset();
};