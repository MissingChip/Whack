
#pragma once

#include "position.h"

#include <limits>
#include <mutex>
#include <string>
#include <vector>

class Widget
{
    struct Cage{
        Pos min;
        Pos max;
    };
public:
    Widget();
    
    void update(){};
    double get_x();
    double get_y();
    double get_w();
    double get_h();
    Rose global_box();

    double get_min_w();
    double get_min_h();
    double get_max_w();
    double get_max_h();

    double full_w();
    double full_h();
    double full_min_w();
    double full_min_h();
    double full_max_w();
    double full_max_h();
    const Rose& get_box();

    double set_x(double x);
    double set_y(double y);
    double set_w(double w);
    double set_h(double h);
    void set_min_w(double w);
    void set_min_h(double h);
    void set_max_w(double w);
    void set_max_h(double h);
    void resize(double w, double h);
    void set_pos(const Pos& p);
    void set_pos(double x, double y);
    void set_size(const Pos& s);
    void set_size(double w, double h);
    void set_min_size(const Pos& s);
    void set_min_size(double w, double h);
    void set_max_size(const Pos& s);
    void set_max_size(double w, double h);
    const Rose& set_box(const Rose& b);
    void set_pad_top(double x);
    void set_pad_right(double x);
    void set_pad_bottom(double x);
    void set_pad_left(double x);
    void set_padding(Rose& pad);
    void set_cage(const Cage& c);

    std::string to_string();

    Rose padding;
//protected:
    void reparent(Widget* parent);
    Widget* parent;

    uint id;

    AnchorLoc stick = ALL;
    Rose box;
    Cage cage;
    Pos flex;
    Pos child_size;

    void (*on_click)();
    void (*on_resize)(double w, double h);

//private:
    uint snatch_id();
    struct ID
    {
        uint id = 0;
        std::mutex mtx;
    };
    static ID id_track;

};

std::string to_string_xywh(Rose);