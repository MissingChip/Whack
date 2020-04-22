
#include "tile.h"
#include "group.h"

Vec2 Tile::global_pos(){
    if(parent){
        return pos + parent->global_pos();
    }
    return pos;
}