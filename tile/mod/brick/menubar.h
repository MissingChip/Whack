#pragma once

#include "mods.h"
#include "brick.h"

#include <vector>

class MenuBar : public Brick {
public:
    MenuBar(int numopts=5);
    virtual ~MenuBar();
    RowMod rowmod = RowMod(0);
    StretchMod stretchmod = StretchMod(anchors::vertical);
};