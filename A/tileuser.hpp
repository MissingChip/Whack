#include "tileuser.h"

inline uint TileUser::get_id(){
    return get_tile()->get_id();
}
inline double TileUser::delta_time(){
    return tile->delta_time();
}

inline double TileUser::get_x(){
    return tile->get_x();
}
inline double TileUser::get_y(){
    return tile->get_y();
}
inline double TileUser::get_w(){
    return tile->get_w();
}
inline double TileUser::get_h(){
    return tile->get_h();
}
inline const Rose& TileUser::get_box(){
    return tile->get_box();
}
inline AnchorLoc TileUser::get_stick(){
    return tile->stick;
}
inline double TileUser::get_min_w(){
    return tile->get_min_w();
}
inline double TileUser::get_min_h(){
    return tile->get_min_h();
}
inline double TileUser::get_max_w(){
    return tile->get_max_w();
}
inline double TileUser::get_max_h(){
    return tile->get_max_h();
}

inline double TileUser::set_x(double x){
    return tile->set_x(x);
}
inline double TileUser::set_y(double x){
    return tile->set_y(x);
}
inline double TileUser::set_w(double x){
    return tile->set_w(x);
}
inline double TileUser::set_h(double x){
    return tile->set_h(x);
}
inline void TileUser::set_min_w(double x){
    return tile->set_min_w(x);
}
inline void TileUser::set_min_h(double x){
    return tile->set_min_h(x);
}
inline void TileUser::set_max_w(double x){
    return tile->set_max_w(x);
}
inline void TileUser::set_max_h(double x){
    return tile->set_max_h(x);
}
inline void TileUser::set_pos(const Pos& b){
    tile->set_pos(b);
}
inline void TileUser::set_pos(double x, double y){
    tile->set_pos(x, y);
}
inline void TileUser::set_size(const Pos& b){
    tile->set_size(b.w, b.h);
}
inline void TileUser::set_size(double w, double h){
    tile->set_size(w, h);
}
inline void TileUser::resize(double w, double h){
    tile->resize(w, h);
}
inline void TileUser::set_min_size(const Pos& b){
    tile->set_min_size(b.w, b.h);
}
inline void TileUser::set_min_size(double w, double h){
    tile->set_min_size(w, h);
}
inline void TileUser::set_max_size(const Pos& b){
    tile->set_max_size(b.w, b.h);
}
inline void TileUser::set_max_size(double w, double h){
    tile->set_max_size(w, h);
}
inline void TileUser::set_box(const Rose& b){
    set_x(b.x);
    set_y(b.y);
    set_w(b.w);
    set_h(b.h);
}

inline void TileUser::set_pad_top(double x){
   tile->set_pad_top(x);
}
inline void TileUser::set_pad_bottom(double x){
   tile->set_pad_bottom(x);
}
inline void TileUser::set_pad_left(double x){
   tile->set_pad_left(x);
}
inline void TileUser::set_pad_right(double x){
   tile->set_pad_right(x);
}
inline void TileUser::set_padding(Rose& pad){
    tile->set_padding(pad);
}

inline void TileUser::set_cage(const Cage& c){
    tile->set_cage(c);
}
inline void TileUser::set_stick(AnchorLoc on){
    tile->set_stick(on);
}