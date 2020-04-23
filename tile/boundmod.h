#pragma once

#include "modifier.h"

class BoundMod : public Modifier {
public:
    float top = 0;
    float right = 0;
    float bottom = 0;
    float left = 0;
    bool force_size = 1;
    bool bind_x = 1;
    bool bind_y = 1;
    virtual void apply(Group*);
};