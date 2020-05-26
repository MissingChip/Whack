#pragma once

#include "brick.h"

class Drag : public Brick {
public:
    Drag();
    virtual ~Drag();

    int drag = 0;
    glm::vec2 trigger_pos;
    double trigger_time;

    virtual void clicked(glm::vec2 pos, int button);
    virtual void mouse(glm::vec2 pos);
    virtual void released(glm::vec2 pos, int button);

};