#pragma once

#include "brick.h"

class Split : public Brick {
public:

    Split(Brick* b1, Brick* b2);

    int dir = 0;
    bool drag;
    float threshold = 10;
    virtual void update();

    virtual void clicked(glm::vec2 pos, int button);
    virtual void mouse(glm::vec2 pos);
    virtual void released(glm::vec2 pos, int button);
};