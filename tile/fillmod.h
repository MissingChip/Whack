#pragma once

#include "modifier.h"
#include <cstdio>

class FillMod : public Modifier{
public:
    FillMod(int direction=1) : direction{direction}{};
    int index = -1;
    int direction = 1;
    virtual void apply(Group*);
};