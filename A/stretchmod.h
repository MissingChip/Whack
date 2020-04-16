#pragma once

#include "modifier.h"

class StretchMod : public Modifier{
public:
    int direction;
    virtual void apply(Group*);
};