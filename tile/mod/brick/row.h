#pragma once

#include "brick.h"
#include "mods.h"

class Row : public Brick{
public:
    Group group;
    AlignMod alignmod = AlignMod();
    RowMod rowmod = RowMod();

    Row();
    //virtual ~Row();
};