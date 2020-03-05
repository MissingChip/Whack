
#pragma once

#include "box.h"

class FixBox : public Box
{
    virtual void update();
    void set_anchor(Tile& w, const Anchor& a);
    void set_anchor(Tile* w, const Anchor* a);
    std::vector<Anchor> anchors;
};