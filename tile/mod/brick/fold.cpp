
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
        if(bricks.size() == 1){
            dir = -1;
        }
        Group* g = static_cast<Group*>(tile);
        for(int i=0;i<g->in.size();i++){
            Tile* t = g->in[i];
            int a[2] {0,0};
            int dout = -2;
            for(int d=0;d<2;d++){
                if(pos[d] - trigger[d] < t->pos[d] && pos[d] > t->pos[d]){
                    a[d] = 1;
                }
                else if(pos[d] + trigger[d] > t->pos[d] + t->size[d] && pos[d] < t->pos[d] + t->size[d]){
                    a[d] = 2;
                }
                if(a[d]){
                    trigger_pos[d] = t->pos[d];
                    anchor_pos[d] = t->pos[d] + t->size[d];
                    dout = d;
                }
            }
            //corner
            if(a[0] && a[1]){
                created = false;
                drag = i+1;
                break;
            }
            //edge
            else if (dout == dir){
                if( int b = a[0] | a[1] ){
                    created = true;
                    drag = 0;
                    if(i < g->in.size()-1 && b == 2){
                        trigger_pos = t->pos;
                        anchor_pos = g->in[i+1]->pos + g->in[i+1]->size;
                        drag = i+1;
                    }
                    if(i > 0 && b == 1){
                        trigger_pos = g->in[i-1]->pos;
                        anchor_pos = t->pos + t->size;
                        drag = i;
                    }
                    break;
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
        Brick* br = bricks[drag-1];
        for(int d=0;d<2;d++){
            if(!dir_unset() && dir != d){
                continue;
            }
            if(!created && pos[d] - trigger[d]*2 > br->tile->pos[d] && pos[d] + trigger[d]*2 < br->tile->pos[d] + br->tile->size[d]){
                if(dir_unset()){
                    dir = d;
                }
                if(dir == d){
                    Brick* b = new_empty();
                    //b->tile->pos[d] = anchor_pos[d];
                    insert(b, drag);
                    created = true;
                }
            }
            if(created && dir == d){
                bricks[drag-1]->tile->size[d] = pos[d] - bricks[drag-1]->tile->pos[d];
                bricks[drag]->tile->size[d] = anchor_pos[d] - pos[d];
                bricks[drag]->tile->pos[d] = pos[d];

                if(pos[d] < trigger_pos[d] + trigger[d]){
                    bricks[drag]->tile->pos = bricks[drag-1]->tile->pos;
                    bricks[drag]->tile->size[d] += bricks[drag-1]->tile->size[d];
                    remove(drag-1);
                    created = false;
                }
                if(pos[d] > anchor_pos[d] - trigger[d]){
                    bricks[drag-1]->tile->size[d] += bricks[drag]->tile->size[d];
                    remove(drag);
                    created = false;
                }
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