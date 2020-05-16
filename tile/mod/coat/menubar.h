#pragma once

#include "mods.h"
#include "coat.h"

#include <vector>

class MenuBar : public Coat {
public:
    MenuBar(int numopts=5);
    virtual ~MenuBar();
    RowMod rowmod = RowMod(0);
    StretchMod stretchmod = StretchMod(anchors::vertical);
};