
#include "tile.h"
#include "group.h"

glm::vec2 Tile::global_pos(){
    if(parent){
        return pos + parent->global_pos();
    }
    return pos;
}

void Tile::shout(){
    if(parent){
        parent->shout();
    }
}
