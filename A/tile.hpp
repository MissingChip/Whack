#pragma once

#include "tile.h"

using namespace std;

inline uint Tile::get_id(){
    return id;
}
inline Tile* Tile::child(int i){
    return nullptr;
}
inline void Tile::click(double x, double y){
    clicked = true;
    if(on_click){
        on_click(x, y, id);
    }
}
inline void Tile::hover(double x, double y){
    if(on_hover){
        on_hover(x, y, id);
    }
}
inline void Tile::release(double x, double y){
    clicked = false;
    if(on_release){
        on_release(x, y, id);
    }
}
inline double Tile::delta_time(){
    double tn = get_time();
    double t = tn-past_time;
    past_time = tn;
    return t;
}
inline double Tile::get_time(){
    return (double)clock()/CLOCKS_PER_SEC;
}

inline double Tile::get_x(){
    return box.x;
}
inline double Tile::get_y(){
    return box.y;
}
inline double Tile::get_w(){
    return box.w;
}
inline double Tile::get_h(){
    return box.h;
}
inline const Rose& Tile::get_box(){
    return box;
}
inline AnchorLoc Tile::get_stick(){
    return stick;
}
inline bool Tile::is_clicked(){
    return clicked;
}
inline double Tile::get_min_w(){
    return max(cage.min.w, child_size.w);
}
inline double Tile::get_min_h(){
    return max(cage.min.h, child_size.h);
}
inline double Tile::get_max_w(){
    return cage.max.w;
}
inline double Tile::get_max_h(){
    return cage.max.h;
}
inline double Tile::full_w(){
    return get_w() + padding.left + padding.right;
}
inline double Tile::full_h(){
    return get_h() + padding.top + padding.bottom;
}
inline double Tile::full_min_w(){
    return get_min_w() + padding.left + padding.right;
}
inline double Tile::full_min_h(){
    return get_min_h() + padding.top + padding.bottom;
}
inline double Tile::full_max_w(){
    return get_max_w() + padding.left + padding.right;
}
inline double Tile::full_max_h(){
    return get_max_h() + padding.top + padding.bottom;
}


inline double Tile::set_x(double x){
    return box.x = x;
}
inline double Tile::set_y(double y){
    return box.y = y;
}
inline double Tile::set_w(double w){
    return box.w = wclamp(w, get_min_w(), get_max_w());
}
inline double Tile::set_h(double h){
    return box.h = wclamp(h, get_min_h(), get_max_h());
}
inline void Tile::set_min_w(double w){
    cage.min.w = w;
}
inline void Tile::set_min_h(double h){
    cage.min.h = h;
}
inline void Tile::set_max_w(double w){
    cage.max.w = w;
}
inline void Tile::set_max_h(double h){
    cage.max.h = h;
}
inline void Tile::set_pos(const Pos& b){
    set_x(b.x);
    set_y(b.y);
}
inline void Tile::set_pos(double x, double y){
    set_x(x);
    set_y(y);
}
inline void Tile::set_size(const Pos& b){
    set_size(b.w, b.h);
}
inline void Tile::set_size(double w, double h){
    if(w>=0){ set_w(w); };
    if(h>=0){ set_h(h); };
    if(on_resize){
        on_resize(w, h, id);
    }
}
inline void Tile::resize(double w, double h){
    set_size(w, h);
}
inline void Tile::set_min_size(const Pos& b){
    set_min_size(b.w, b.h);
}
inline void Tile::set_min_size(double w, double h){
    if(w>=0){set_min_w(w);}
    if(h>=0){set_min_h(h);}
}
inline void Tile::set_max_size(const Pos& b){
    set_max_size(b.w, b.h);
}
inline void Tile::set_max_size(double w, double h){
    if(w>=0){set_max_w(w);}
    if(h>=0){set_max_h(h);}
}
inline const Rose& Tile::set_box(const Rose& b){
    set_x(b.x);
    set_y(b.y);
    set_w(b.w);
    set_h(b.h);
    return box;
}

inline void Tile::set_pad_top(double x){
    padding.top = x;
}
inline void Tile::set_pad_right(double x){
    padding.right = x;
}
inline void Tile::set_pad_bottom(double x){
    padding.bottom = x;
}
inline void Tile::set_pad_left(double x){
    padding.left = x;
}

inline void Tile::set_padding(Rose& pad){
    padding = pad;
}
inline void Tile::set_cage(const Cage& c){
    cage = c;
}
inline void Tile::set_stick(AnchorLoc on){
    stick = on;
}

inline void Tile::reparent(Tile *w){
    parent = w;
}
