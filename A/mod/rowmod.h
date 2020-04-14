#pragma once

#include "modifier.h"

class RowMod : public Modifier{
    bool direction;
    float spacing;

    virtual void apply(Group*);
private: /* helpers */
};