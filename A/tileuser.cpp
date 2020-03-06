
#include "tileuser.h"

TileUser::TileUser(){
}
TileUser::~TileUser(){
    if(tile){
        delete tile;
        tile = nullptr;
    }else{
        fprintf(stderr, "tile for TileUser %u was never assigned - you live dangerously\n", get_id());
    }
}
Tile* TileUser::get_tile(){
    return tile;
}
void TileUser::tile_init(){
    tile = get_tile();
    if(tile){
        id = tile->id;
    }
}
void TileUser::click(double x, double y){
    tile->click(x, y);
}
void TileUser::hover(double x, double y){
    tile->hover(x, y);
}
void TileUser::release(double x, double y){
    tile->release(x, y);
}
void TileUser::update(){
    tile->update();
}

Pos TileUser::global_pos(){
    return tile->global_pos();
}
Rose TileUser::global_box(){
    return tile->global_box();
}
