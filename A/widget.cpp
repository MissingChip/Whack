
#include "wmath.h"
#include "widget.h"
#include <time.h>

using namespace std;

Widget::Widget(){
    snatch_id();
    cage = {{0, 0}, {numeric_limits<double>::infinity(), numeric_limits<double>::infinity()}};
}

string Widget::to_string(){
    return "W:" + to_string_xywh(box);
}
string Widget::inner_info(){
    return "";
}
Widget* Widget::child(int i){
    return nullptr;
}
void Widget::wk_render(void* data){
    printf("%s\n", to_string().c_str());
}
void Widget::click(double x, double y){
    clicked = true;
    if(on_click){
        on_click(x, y, this);
    }
}
void Widget::hover(double x, double y){
    if(on_hover){
        on_hover(x, y, this);
    }
}
void Widget::release(double x, double y){
    clicked = false;
    if(on_release){
        on_release(x, y, this);
    }
}
double Widget::delta_time(){
    double tn = get_time();
    double t = tn-past_time;
    past_time = tn;
    return t;
}
double Widget::get_time(){
    return (double)clock()/CLOCKS_PER_SEC;
}

#ifndef WIDGET_INLINE
double Widget::get_x(){
    return box.x;
}
double Widget::get_y(){
    return box.y;
}
double Widget::get_w(){
    return box.w;
}
double Widget::get_h(){
    return box.h;
}
const Rose& Widget::get_box(){
    return box;
}
bool Widget::get_clicked(){
    return clicked;
}
Pos Widget::global_pos(){
    if(parent){
        Pos o = parent->global_pos();
        return Pos{o.x+box.x, o.y+box.y};
    }
    return Pos{box.x, box.y};
}
Rose Widget::global_box(){
    if(parent){
        Pos o = parent->global_pos();
        return Rose{o.x+box.x, o.y+box.y, box.w, box.h};
    }
    return box;
}
double Widget::get_min_w(){
    return max(cage.min.w, child_size.w);
}
double Widget::get_min_h(){
    return max(cage.min.h, child_size.h);
}
double Widget::get_max_w(){
    return cage.max.w;
}
double Widget::get_max_h(){
    return cage.max.h;
}
double Widget::full_w(){
    return get_w() + padding.left + padding.right;
}
double Widget::full_h(){
    return get_h() + padding.top + padding.bottom;
}
double Widget::full_min_w(){
    return get_min_w() + padding.left + padding.right;
}
double Widget::full_min_h(){
    return get_min_h() + padding.top + padding.bottom;
}
double Widget::full_max_w(){
    return get_max_w() + padding.left + padding.right;
}
double Widget::full_max_h(){
    return get_max_h() + padding.top + padding.bottom;
}


double Widget::set_x(double x){
    return box.x = x;
}
double Widget::set_y(double y){
    return box.y = y;
}
double Widget::set_w(double w){
    return box.w = wclamp(w, get_min_w(), get_max_w());
}
double Widget::set_h(double h){
    return box.h = wclamp(h, get_min_h(), get_max_h());
}
void Widget::set_min_w(double w){
    cage.min.w = w;
}
void Widget::set_min_h(double h){
    cage.min.h = h;
}
void Widget::set_max_w(double w){
    cage.max.w = w;
}
void Widget::set_max_h(double h){
    cage.max.h = h;
}
void Widget::set_pos(const Pos& b){
    set_x(b.x);
    set_y(b.y);
}
void Widget::set_pos(double x, double y){
    set_x(x);
    set_y(y);
}
void Widget::set_size(const Pos& b){
    set_size(b.w, b.h);
}
void Widget::set_size(double w, double h){
    if(w>=0){ set_w(w); }else{w=get_w();};
    if(h>=0){ set_h(h); }else{h=get_h();};
    if(on_resize){
        on_resize(w, h, this);
    }
}
void Widget::resize(double w, double h){
    set_size(w, h);
}
void Widget::set_min_size(const Pos& b){
    set_min_size(b.w, b.h);
}
void Widget::set_min_size(double w, double h){
    set_min_w(w);
    set_min_h(h);
}
void Widget::set_max_size(const Pos& b){
    set_max_size(b.w, b.h);
}
void Widget::set_max_size(double w, double h){
    set_max_w(w);
    set_max_h(h);
}
const Rose& Widget::set_box(const Rose& b){
    set_x(b.x);
    set_y(b.y);
    set_w(b.w);
    set_h(b.h);
    return box;
}

void Widget::set_pad_top(double x){
    padding.top = x;
}
void Widget::set_pad_right(double x){
    padding.right = x;
}
void Widget::set_pad_bottom(double x){
    padding.bottom = x;
}
void Widget::set_pad_left(double x){
    padding.left = x;
}

void Widget::set_padding(Rose& pad){
    padding = pad;
}
void Widget::set_cage(const Cage& c){
    cage = c;
}

void Widget::reparent(Widget *w){
    parent = w;
}
#endif

uint Widget::snatch_id()
{
    id_track.mtx.lock();
    id = id_track.id++;
    id_track.mtx.unlock();
    return id;
}

Widget::ID Widget::id_track;

/*
std::string to_string_xywh(Rose r)
{
    char a[256];
    sprintf(a, "[x: %.2f, y: %.2f, w: %.2f, h: %.2f]", r.x, r.y, r.w, r.h);
    return string(a);
}*/