#pragma once

#include "modifier.h"

class StretchMod : public Modifier{
    int direction;
    virtual void apply(Group*);
};