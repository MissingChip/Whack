#pragma once

#include "modifier.h"

class MarginMod : public Modifier {
public:
    MarginMod(float ud, float lr);
    MarginMod(float t, float r, float b, float l);
    float top;
    float right;
    float bottom;
    float left;
    bool fill=1;
    virtual void apply(Group*);
};