#pragma once

#include <vector>
#include <glm/vec2.hpp>
#include "tile.h"

class Brick {
public:
    Tile* tile = nullptr;
    //Brick* parent = nullptr;
    std::vector<Brick*> bricks;
    bool forward_outclick = false;
    bool forward_outmouse = false;
    bool forward_outrelease = false;

    void set_w(float w);
    void set_h(float w);
    void set_x(float w);
    void set_y(float w);
    void set_pos(glm::vec2 pos);
    void set_size(glm::vec2 size);

    float get_w();
    float get_h();
    float get_x();
    float get_y();
    const glm::vec2& get_pos();
    const glm::vec2& get_size();

    void attach(Tile* t);
    bool is_inside(glm::vec2 pos);
    void forward_all(bool f = true);
    void forward_nonclick(bool f = true);
    virtual void update();
    //virtual void shout();
    virtual void add(Brick* p);
    virtual void insert(Brick* p, int index);
    virtual void remove(Brick* p);
    virtual void remove(uint index);
    virtual int idx_of(Brick* p);
    virtual void replace(Brick* b1, Brick* b2);
    virtual void replace(uint idx1, Brick* b2);
    virtual int interact(const glm::vec2& pos);
    virtual int check_interact(const glm::vec2& pos);

    virtual void clicked(glm::vec2 pos, int button);
    virtual void mouse(glm::vec2 pos);
    virtual void released(glm::vec2 pos, int button);
    //virtual void clicked_off(glm::vec2 pos);
    void (*on_click)(glm::vec2 pos, int button) = nullptr;
    void (*on_mouse)(glm::vec2 pos) = nullptr;
    void (*on_release)(glm::vec2 pos, int button) = nullptr;

    static const uint update_threshold = 8;
};

inline void Brick::set_w(float w){
    tile->size.x = w;
}
inline void Brick::set_h(float h){
    tile->size.y = h;
}
inline void Brick::set_x(float x){
    tile->pos.x = x;
}
inline void Brick::set_y(float y){
    tile->pos.y = y;
}
inline void Brick::set_size(glm::vec2 s){
    tile->size = s;
}
inline void Brick::set_pos(glm::vec2 s){
    tile->pos = s;
}

inline float Brick::get_w(){
    return tile->size.x;
}
inline float Brick::get_h(){
    return tile->size.y;
}
inline float Brick::get_x(){
    return tile->pos.x;
}
inline float Brick::get_y(){
    return tile->pos.y;
}
inline const glm::vec2& Brick::get_pos(){
    return tile->pos;
}
inline const glm::vec2& Brick::get_size(){
    return tile->size;
}