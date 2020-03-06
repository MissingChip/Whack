
#include "tileuser.h"

TileUser::TileUser(){
    add_user(this);
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
    id = tile->id;
    add_user(this);
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

void TileUser::add_user(TileUser* t){
    users_mutex.lock();
    if(t->id > tile_users.size()){
        tile_users.resize(t->id);
    }
    tile_users[t->id] = t;
    users_mutex.unlock();
}