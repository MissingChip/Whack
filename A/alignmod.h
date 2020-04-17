#pragma once

#include "modifier.h"

class AlignMod : public Modifier{
public:
    int anchor = anchors::left;

    void anchor_to(int a){anchor = a;};

    virtual void apply(Group*);
    virtual void align_tile(Tile* t, Group* g);
private: /* helpers */
};