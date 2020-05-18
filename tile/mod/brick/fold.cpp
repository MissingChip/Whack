
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
        Group* g = static_cast<Group*>(tile);
        for(int i=0;i<g->in.size();i++){
            Tile* t = g->in[i];
            if(pos.x + trigger.x > t->pos.x + t->size.x && pos.x < t->pos.x + t->size.x){
                if( pos.y < trigger.y ){
                    drag = i+1;
                    trigger_pos = glm::vec2(t->pos.x+t->size.x, 0);
                }else if(dir == 0 && g->in.size()-1 > i){
                    drag = i+1;
                    trigger_pos = glm::vec2(g->in[i+1]->pos.x+g->in[i+1]->size.x, 0);
                    created = true;
                }
            }
            else if(pos.x - trigger.x < t->pos.x + t->size.x && pos.x > t->pos.x + t->size.x){
                if( pos.y < trigger.y ){
                    drag = i+1;
                    trigger_pos = glm::vec2(t->pos.x+t->size.x, 0);
                }else if(dir == 0 && g->in.size()-1 > i){
                    drag = i+1;
                    trigger_pos = glm::vec2(g->in[i+1]->pos.x+g->in[i+1]->size.x, 0);
                    created = true;
                }
            }
        }
    }
    else{
        Brick::clicked(pos, button);
    }
}

void Fold::mouse(glm::vec2 pos){
    //printf("moused fold %f %f\n", pos.x, pos.y);
    if(drag){
        if(bricks.size() == 1){
            dir = -1;
        }
        for(int i=0;i<2;i++){
            if(pos[i] < trigger_pos[i]-trigger[i]*2){
                if(dir_unset()){
                    dir = i;
                }
                if(dir == i){
                    if(!created){
                        Brick* b = new_empty();
                        b->tile->pos = glm::vec2(trigger_pos[i], 0);
                        insert(b, drag);
                        created = true;
                    }
                    Brick* b = bricks[drag-1];
                    
                    if(pos[i] > bricks[drag-1]->tile->pos[i] + trigger[i]){
                        bricks[drag-1]->tile->size[i] = pos[i] - bricks[drag-1]->tile->pos[i];
                        bricks[drag]->tile->size[i] = trigger_pos[i] - pos[i];
                        bricks[drag]->tile->pos[i] = pos[i];
                    }
                    else{
                        bricks[drag-1]->tile->size[i] = trigger[i];
                        bricks[drag]->tile->size[i] = trigger_pos[i] - bricks[drag-1]->tile->size[i] - bricks[drag-1]->tile->pos[i];
                        bricks[drag]->tile->pos[i] = bricks[drag-1]->tile->pos[i] + trigger[i];
                    }
                }
            }
            if(created && pos[i] > trigger_pos[i] - trigger[i] && dir == i){
                bricks[drag-1]->tile->size[i] += bricks[drag]->tile->size[i];
                remove(bricks[drag]);
                //TODO this is definitely a memory leak but so is this entire thing so I should come back and think about that
                created = false;
            }
        }
    }
    else{
        Brick::mouse(pos);
    }
}

void Fold::released(glm::vec2 pos, int button){
    if(drag){
        drag = 0;
        created = false;
    }
    else{
        Brick::clicked(pos, button);
    }
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