
#pragma once
//#define WIDGET_INLINE

#include "position.h"
#include "wmath.h"

#include <limits>
#include <mutex>
#include <string>
#include <vector>

class Tile
{
public:
    Rose box;
    Tile();
    ~Tile();
    
    virtual void update(){};
    virtual Tile* child(int i);
    uint get_id();
    static Tile* by_id(uint id);

    virtual void click(double x, double y);
    virtual void hover(double x, double y);
    virtual void release(double x, double y);
    static double get_time();
    double past_time = 0;
    double delta_time();

    void (*on_click)(double x, double y, Tile* wk) = nullptr;
    void (*on_release)(double x, double y, Tile* wk) = nullptr;
    void (*on_hover)(double x, double y, Tile* wk) = nullptr;
    void (*on_resize)(double w, double h, Tile* wk) = nullptr;
    static Pos (*get_mouse_pos)(Tile* wk);

    double get_x();
    double get_y();
    double get_w();
    double get_h();
    Pos global_pos();
    Rose global_box();
    bool is_clicked();

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

    Rose padding = Rose{0,0,0,0};
//protected:
    void reparent(Tile* parent);
    Tile* parent = nullptr;

    uint id;

    AnchorLoc stick = ALL;
    Cage cage;
    Pos flex = Pos{0,0};
    Pos child_size = Pos{0,0};
    bool clicked = false;
    Pos mouse = Pos{0,0};

private:
    uint snatch_id();
    template<class T>
    struct ID
    {
        uint id = 0;
        std::vector<T*> tiles;
        std::mutex mtx;
    };
    static ID<Tile> id_track;
};

std::string to_string_xywh(Rose);

#include "tile.hpp"