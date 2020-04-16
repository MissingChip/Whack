#pragma once

#include "modifier.h"

class MarginMod : public Modifier {
    float top;
    float right;
    float bottom;
    float left;
    virtual void apply(Group*);
};