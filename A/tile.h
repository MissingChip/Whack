#pragma once
#include "vec.h"
class Box;

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

    virtual void update();
    virtual void update_all();
    Vec2 global_pos();
};

Tile::Tile()
{
}
Tile::Tile(float x, float y, float w, float h)
{
    pos.x = x;
    pos.y = y;
    size.x = w;
    size.y = h;
}

Tile::~Tile()
{
}

inline Vec2 Tile::global_pos(){
    if(parent){
        return pos + parent->global_pos();
    }
    return pos;
}