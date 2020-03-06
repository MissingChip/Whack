#pragma once

#include "tile.h"

class TileUser
{
public:
    TileUser();
    ~TileUser();
    Tile* tile = nullptr;
    TileUser* parent;
    uint id;
    uint get_id();
    void tile_init();
    virtual Tile* get_tile();
    virtual void update();

    virtual void click(double x, double y);
    virtual void hover(double x, double y);
    virtual void release(double x, double y);
    double past_time = 0;
    double delta_time();

    double get_x();
    double get_y();
    double get_w();
    double get_h();
    Pos global_pos();
    Rose global_box();

    double get_min_w();
    double get_min_h();
    double get_max_w();
    double get_max_h();

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
    void set_box(const Rose& b);
    void set_pad_top(double x);
    void set_pad_right(double x);
    void set_pad_bottom(double x);
    void set_pad_left(double x);
    void set_padding(Rose& pad);
    void set_cage(const Cage& c);

private:
    static vector<TileUser*> tile_users;
    static std::mutex users_mutex;
    static void add_user(TileUser* t);
};

#include "tileuser.hpp"