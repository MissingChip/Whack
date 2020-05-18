
#include <cstdio>

#include "fold.h"
#include "group.h"

Fold::Fold(){
    tile = new Group;
    Brick* b = new_empty();
    add(b);
}
Fold::~Fold(){
    delete tile;
}

void Fold::clicked(glm::vec2 pos, int button){
    if(!drag){
        if(pos.x-tile->size.x < trigger.x && pos.y < trigger.y){
            drag = bricks.size();
            trigger_pos = glm::vec2(tile->size.x, 0);
        }
    }
}

void Fold::mouse(glm::vec2 pos){
    //printf("moused fold %f %f\n", pos.x, pos.y);
    if(drag){
        if(trigger_pos.x-pos.x>trigger.x*2){
            if(dir_unset()){
                dir = 0;
            }
            if(dir == 0){
                //printf("aaaa\n");
                if(!created){
                    Brick* b = new_empty();
                    b->tile->pos = glm::vec2(trigger_pos.x, 0);
                    insert(b, drag);
                    created = true;
                }
                Brick* b = bricks[drag-1];
                
                if(pos.x > bricks[drag-1]->tile->pos.x + trigger.x){
                    bricks[drag-1]->tile->size.x = pos.x - bricks[drag-1]->tile->pos.x;
                    bricks[drag]->tile->size.x = trigger_pos.x - pos.x;
                    bricks[drag]->tile->pos.x = pos.x;
                }
                else{
                    bricks[drag-1]->tile->size.x = trigger.x;
                    bricks[drag]->tile->size.x = trigger_pos.x - bricks[drag-1]->tile->size.x - bricks[drag-1]->tile->pos.x;
                    bricks[drag]->tile->pos.x = bricks[drag-1]->tile->pos.x + trigger.x;
                }
            }
        }
    }
}

void Fold::released(glm::vec2 pos, int button){
    drag = 0;
    created = false;
}

void Fold::update(){
    if(dir == -1){
        Group* g = static_cast<Group*>(tile);
        g->in[0]->size = g->size;
        psize = tile->size;
    }
    else if(psize != tile->size){
        double r = tile->size[dir]/psize[dir];
        Group* g = static_cast<Group*>(tile);
        for(int i = 0; i<g->in.size()-1;i++){
            Tile* t = g->in[i];
            t->size[dir] *= r;
            t->size[!dir] = tile->size[!dir];
            g->in[i+1]->pos[dir] = t->pos[dir] + t->size[dir];
        }
        g->in[g->in.size()-1]->size[dir] = g->size[dir] - g->in[g->in.size()-1]->pos[dir];
        g->in[g->in.size()-1]->size[!dir] = tile->size[!dir];
        psize = tile->size;
    }
    Brick::update();
}

Brick* Fold::new_empty(){
    Brick* b = new Brick();
    b->tile = new Tile();
    b->tile->size = tile->size;
    return b;
}
bool Fold::dir_unset(){
    return dir == -1;
}