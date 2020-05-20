
#include "split.h"
#include "group.h"

#include <cstdio>
#include <math.h>

Split::Split(Brick* b1, Brick* b2){
    tile = new Group;
    add(b1);
    add(b2);
}
void Split::update(){
    bricks[0]->tile->size[!dir] = tile->size[!dir];
    bricks[1]->tile->size[!dir] = tile->size[!dir];
    bricks[1]->tile->pos[dir] = bricks[1]->tile->size[dir];
    bricks[1]->tile->size[dir] = tile->size[dir] - bricks[1]->tile->pos[dir];

}
void Split::clicked(glm::vec2 pos, int button){
    if(abs(pos[dir] - bricks[0]->tile->size[dir]) <= threshold && !(check_interact(pos))){
        drag = true;
        return;
    }
    drag = false;
}
void Split::mouse(glm::vec2 pos){
    if(drag){
        if(pos[dir] < threshold) pos[dir] = threshold;
        if(pos[dir] > tile->size[dir] - threshold) pos[dir] = tile->size[dir] - threshold;
        bricks[0]->tile->size[dir] = pos[dir];
        bricks[1]->tile->pos[dir] = pos[dir];
        bricks[1]->tile->size[dir] = tile->size[dir] - pos[dir];
        bricks[0]->update();
        bricks[1]->update();
    }
}
void Split::released(glm::vec2 pos, int button){
    drag = false;
}