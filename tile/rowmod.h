#pragma once

#include "modifier.h"

class RowMod : public Modifier{
public:
    bool direction = 1;
    bool resize_on_update = 0;
    float spacing = 0;

    virtual void apply(Group*);
private: /* helpers */
};