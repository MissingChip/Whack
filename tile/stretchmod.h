#pragma once

#include "modifier.h"

class StretchMod : public Modifier{
public:
    int direction = anchors::right;
    virtual void apply(Group*);
};