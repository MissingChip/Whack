
#include "tile.h"

Tile::Tile(){
    snatch_id();
    cage = {{0, 0}, {numeric_limits<double>::infinity(), numeric_limits<double>::infinity()}};
    delta_time();
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

uint Tile::snatch_id()
{
    id_track.mtx.lock();
    id = id_track.id++;
    id_track.mtx.unlock();
    return id;
}

Tile::ID Tile::id_track;


std::string to_string_xywh(Rose r)
{
    char a[256];
    sprintf(a, "[x: %.2f, y: %.2f, w: %.2f, h: %.2f]", r.x, r.y, r.w, r.h);
    return string(a);
}