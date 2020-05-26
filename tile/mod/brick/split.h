#pragma once

#include "brick.h"
#include "../splitmod.h"

class Split : public Brick {
public:

    Split(Brick* b1, Brick* b2, bool direction = 0);
    virtual ~Split();

    SplitMod split;
    bool& dir = split.dir;
    bool drag;
    float threshold = 10;
    //virtual void update();

    virtual void clicked(glm::vec2 pos, int button);
    virtual void mouse(glm::vec2 pos);
    virtual void released(glm::vec2 pos, int button);
};