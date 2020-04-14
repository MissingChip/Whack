#pragma once
#include "vec.h"
class Group;

class Tile
{
private:
public:
    Vec2 pos;
    Vec2 size;
    Group* parent = nullptr;
    bool in_use;
    //bool visible;

    Tile();
    Tile(float x, float y, float w, float h);
    virtual ~Tile();

    virtual void update(){};
    virtual void update_all(){};
    Vec2 global_pos();
};

inline Tile::Tile()
{
}
inline Tile::Tile(float x, float y, float w, float h)
{
    pos.x = x;
    pos.y = y;
    size.x = w;
    size.y = h;
}
inline Tile::~Tile()
{
}