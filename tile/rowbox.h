#pragma once

#include "group.h"
#include "mod/alignmod.h"
#include "mod/rowmod.h"

class RowBox : public Group {
public:
    AlignMod alignmod = AlignMod();
    RowMod rowmod = RowMod();

    RowBox();
    RowBox(Tile* t) : Group(t){init();};
    virtual ~RowBox();
    void set_direction(bool vertical);
    void set_align(int anchor);
private:
    void init();
};