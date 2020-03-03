//#pragma once
#include "widget.h"
#include "wmath.h"

#ifdef WIDGET_INLINE
inline
double Widget::get_x(){
    return box.x;
}
inline
double Widget::get_y(){
    return box.y;
}
inline
double Widget::get_w(){
    return box.w;
}
inline
double Widget::get_h(){
    return box.h;
}
inline
const Rose& Widget::get_box(){
    return box;
}
inline
Pos Widget::global_pos(){
    if(parent){
        Pos o = parent->global_pos();
        return Pos{o.x+box.x, o.y+box.y};
    }
    return Pos{box.x, box.y};
}
inline
Rose Widget::global_box(){
    if(parent){
        Pos o = parent->global_pos();
        return Rose{o.x+box.x, o.y+box.y, box.w, box.h};
    }
    return box;
}
inline
double Widget::get_min_w(){
    return std::max(cage.min.w, child_size.w);
}
inline
double Widget::get_min_h(){
    return std::max(cage.min.h, child_size.h);
}
inline
double Widget::get_max_w(){
    return cage.max.w;
}
inline
double Widget::get_max_h(){
    return cage.max.h;
}
inline
double Widget::full_w(){
    return get_w() + padding.left + padding.right;
}
inline
double Widget::full_h(){
    return get_h() + padding.top + padding.bottom;
}
inline
double Widget::full_min_w(){
    return get_min_w() + padding.left + padding.right;
}
inline
double Widget::full_min_h(){
    return get_min_h() + padding.top + padding.bottom;
}
inline
double Widget::full_max_w(){
    return get_max_w() + padding.left + padding.right;
}
inline
double Widget::full_max_h(){
    return get_max_h() + padding.top + padding.bottom;
}


inline
double Widget::set_x(double x){
    return box.x = x;
}
inline
double Widget::set_y(double y){
    return box.y = y;
}
inline
double Widget::set_w(double w){
    return box.w = wclamp(w, get_min_w(), get_max_w());
}
inline
double Widget::set_h(double h){
    return box.h = wclamp(h, get_min_h(), get_max_h());
}
inline
void Widget::set_min_w(double w){
    cage.min.w = w;
}
inline
void Widget::set_min_h(double h){
    cage.min.h = h;
}
inline
void Widget::set_max_w(double w){
    cage.max.w = w;
}
inline
void Widget::set_max_h(double h){
    cage.max.h = h;
}
inline
void Widget::set_pos(const Pos& b){
    set_x(b.x);
    set_y(b.y);
}
inline
void Widget::set_pos(double x, double y){
    set_x(x);
    set_y(y);
}
inline
void Widget::set_size(const Pos& b){
    set_w(b.w);
    set_h(b.h);
}
inline
void Widget::set_size(double w, double h){
    set_w(w);
    set_h(h);
}
inline
void Widget::resize(double w, double h){
    set_size(w, h);
}
inline
void Widget::set_min_size(const Pos& b){
    set_min_size(b.w, b.h);
}
inline
void Widget::set_min_size(double w, double h){
    set_min_w(w);
    set_min_h(h);
}
inline
void Widget::set_max_size(const Pos& b){
    set_max_size(b.w, b.h);
}
inline
void Widget::set_max_size(double w, double h){
    set_max_w(w);
    set_max_h(h);
}
inline
const Rose& Widget::set_box(const Rose& b){
    set_x(b.x);
    set_y(b.y);
    set_w(b.w);
    set_h(b.h);
    return box;
}

inline
void Widget::set_pad_top(double x){
    padding.top = x;
}
inline
void Widget::set_pad_right(double x){
    padding.right = x;
}
inline
void Widget::set_pad_bottom(double x){
    padding.bottom = x;
}
inline
void Widget::set_pad_left(double x){
    padding.left = x;
}

inline
void Widget::set_padding(Rose& pad){
    padding = pad;
}
inline
void Widget::set_cage(const Cage& c){
    cage = c;
}

inline
void Widget::reparent(Widget *w){
    parent = w;
}
#endif