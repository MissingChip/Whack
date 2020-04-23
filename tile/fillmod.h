#pragma once

#include "modifier.h"

class FillMod : public Modifier{
public:
    int index = -1;
    int direction = 1;
    virtual void apply(Group*);

};