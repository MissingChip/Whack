#pragma once

#include "modifier.h"

class AlignMod : public Modifier{
    int anchor;

    virtual void apply(Group*);
    virtual void align_tile(Tile* t, Group* g);
private: /* helpers */
};