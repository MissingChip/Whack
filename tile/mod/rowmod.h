#pragma once

#include "modifier.h"

class RowMod : public Modifier{
public:
    RowMod(bool direction=1, float spacing=0, bool resize=0);
    virtual ~RowMod() = default;
    bool direction = 1;
    float spacing = 0;
    bool resize_on_update = 0;

    virtual void apply(Group*);
private: /* helpers */
};