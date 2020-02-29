#pragma once

enum AnchorLoc
{
    none = 0,
    TOP =    0b0001,
    RIGHT =  0b0010,
    BOTTOM = 0b0100,
    LEFT =   0b1000,
    CENTER = 0b1111,
    ALL = CENTER,
    top_left = TOP | LEFT,
    top = TOP,
    top_right = TOP | RIGHT,
    right = RIGHT,
    bottom_right = BOTTOM | RIGHT,
    bottom = BOTTOM,
    bottom_left = BOTTOM | LEFT,
    left = LEFT,
    center_v = TOP | BOTTOM,
    center_h = LEFT | RIGHT,
    center = TOP | BOTTOM | RIGHT | LEFT,
    all = ALL
};

struct Anchor
{
    double x;
    double y;
    AnchorLoc type;
};

struct Pos
{
    union{ double x, w, left, top; };
    union{ double y, h, l, right, bottom; };
};

struct Rose
{
    /*
     * safe combinations:
     *    (elemnts not neccessarily in order)
     * <x, y, z, w>
     * <x, y, w, h>
     * <x1, y1, x2, y2>
     * <N, S, E, W>
     */
    union{ double left, x, x1, E; };
    union{ double top, y, y1, N; };
    union{ double right, w, x2, W; };
    union{ double bottom, h, y2, S, z; };
};

inline bool is_side(AnchorLoc a){
    return (a == TOP || a == LEFT || a == RIGHT || a == BOTTOM);
}