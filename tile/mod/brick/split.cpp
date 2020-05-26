
#include "split.h"
#include "group.h"

#include <cstdio>
#include <math.h>

Split::Split(Brick* b1, Brick* b2, bool direction) : split{0, 0, 124} {
    dir = direction;
    Group* g = new Group;
    tile = g;
    add(b1);
    add(b2);
    g->add(&split);
}
Split::~Split(){}
/*
void Split::update(){
    bricks[0]->tile->size[!dir] = tile->size[!dir];
    bricks[1]->tile->size[!dir] = tile->size[!dir];
    bricks[0]->tile->pos = glm::vec2(0,0);
    bricks[0]->tile->pos[!dir] = 0;
    bricks[1]->tile->pos[dir] = bricks[1]->tile->size[dir];
    bricks[1]->tile->size[dir] = tile->size[dir] - bricks[1]->tile->pos[dir];
}*/
void Split::clicked(glm::vec2 pos, int button){
    if(abs(pos[dir] - bricks[0]->tile->size[dir]) <= threshold && !(check_interact(pos))){
        drag = true;
        return;
    }
    drag = false;
    Brick::clicked(pos, button);
}
void Split::mouse(glm::vec2 pos){
    if(drag){
        float a = pos[dir];
        if(a < threshold*2){
            a = threshold*2;
        }
        else if(a > tile->size[dir] - threshold*2){
            a = tile->size[dir] - threshold*2;
        }
        split.split = a;
        update();
        return;
    }
    Brick::mouse(pos);
}
void Split::released(glm::vec2 pos, int button){
    drag = false;
    Brick::released(pos, button);
}