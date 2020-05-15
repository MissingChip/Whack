#pragma once

#include "coat.h"
#include "mods.h"

class Row : public Coat{
public:
    Group group;
    AlignMod alignmod = AlignMod();
    RowMod rowmod = RowMod();

    Row();
    //virtual ~Row();
};