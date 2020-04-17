#pragma once

#include "group.h"
#include "alignmod.h"
#include "rowmod.h"

class RowBox : public Group {
public:
    AlignMod* alignmod;
    RowMod* rowmod;

    RowBox();
    virtual ~RowBox();
    void set_direction(bool horizontal);
    void set_align(int anchor);
};