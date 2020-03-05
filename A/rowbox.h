
#pragma once

#include "box.h"

#include <vector>

class RowBox : public Box
{
public:
    //virtual void add(Tile* w);
    virtual void update();
    void set_margins(const Rose& margins);
    void set_spacing(const Pos& space);
    void grow_from(AnchorLoc side);
    void attach_to(AnchorLoc side);
protected:
    AnchorLoc attach;
    Rose margins;
    Pos spacing;
private:
    void grow_up();
    void grow_down();
    void grow_right();
    void grow_left();
    AnchorLoc default_stick();
    void stick_Tile(Tile* Tile);
};