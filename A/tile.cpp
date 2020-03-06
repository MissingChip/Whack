
#include "tile.h"

Tile::Tile(){
    id = tracker.add(this);
    cage = {{0, 0}, {numeric_limits<double>::infinity(), numeric_limits<double>::infinity()}};
    delta_time();
}
Tile::~Tile(){
    tracker.remove(id);
}
Tile* Tile::by_id(uint id){
    return tracker[id];
}

Pos Tile::global_pos(){
    if(parent){
        Pos o = parent->global_pos();
        return Pos{o.x+box.x, o.y+box.y};
    }
    return Pos{box.x, box.y};
}
Rose Tile::global_box(){
    if(parent){
        Pos o = parent->global_pos();
        return Rose{o.x+box.x, o.y+box.y, box.w, box.h};
    }
    return box;
}

Tracker<Tile> Tile::tracker;

std::string to_string_xywh(Rose r)
{
    char a[256];
    sprintf(a, "[x: %.2f, y: %.2f, w: %.2f, h: %.2f]", r.x, r.y, r.w, r.h);
    return string(a);
}