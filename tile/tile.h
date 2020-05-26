#pragma once
#include "vec.h"
#include <glm/vec2.hpp>
class Group;

class Tile
{
private:
public:
    glm::vec2 pos;
    glm::vec2 size;
    Group* parent = nullptr;
    //void* data = nullptr;
    bool in_use;
    uint id;
    //bool visible;

    Tile();
    Tile(float x, float y, float w, float h);
    Tile(float w, float h) : Tile(0, 0, w, h) {};
    virtual ~Tile();

    virtual void update(){};
    virtual void update_all(){};
    virtual void shout();
    glm::vec2 global_pos();
    void ssize(glm::vec2& s);
    void spos(glm::vec2& s);
    bool contains(const glm::vec2& pos);
};

inline Tile::Tile()
{
    pos = glm::vec2(0,0);
    size = glm::vec2(0,0);
}
inline Tile::Tile(float x, float y, float w, float h)
{
    pos.x = x;
    pos.y = y;
    size.x = w;
    size.y = h;
}
inline Tile::~Tile()
{
}

inline void Tile::ssize(glm::vec2& s){
    size = s;
}
inline void Tile::spos(glm::vec2& s){
    pos = s;
}
inline bool Tile::contains(const glm::vec2& s){
    return s.x > pos.x && s.y > pos.y && s.x < pos.x + size.x && s.y < pos.y + size.y;
}