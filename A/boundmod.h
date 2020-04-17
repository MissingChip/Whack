#pragma once

#include "modifier.h"

class BoundMod : public Modifier {
    float top = 0;
    float right = 0;
    float bottom = 0;
    float left = 0;
    bool force_size;
    virtual void apply(Group*);
};