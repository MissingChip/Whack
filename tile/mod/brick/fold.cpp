
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
            //right edge (max x)
            if(pos.x + trigger.x > t->pos.x + t->size.x && pos.x < t->pos.x + t->size.x){
                //top
                if( pos.y < trigger.y){
                    drag = i+1;
                    trigger_pos = glm::vec2(t->pos.x+t->size.x, 0);
                    anchor_pos = trigger_pos;
                    break;
                }
                //bottom
                if( pos.y + trigger.y > t->pos.y + t->size.y ){
                    drag = i+1;
                    trigger_pos = glm::vec2(t->pos.x+t->size.x, t->pos.y + t->size.y);
                    anchor_pos = trigger_pos;
                    break;
                }
                //handle right edge
                if(dir == 0 && i < g->in.size()-1){
                    printf("right grab\n");
                    drag = i+1;
                    trigger_pos = glm::vec2(g->in[i+1]->pos.x+g->in[i+1]->size.x, 0);
                    anchor_pos = trigger_pos;
                    created = true;
                    break;
                }
            }
            //left edge (min x)
            else if(pos.x - trigger.x < t->pos.x && pos.x > t->pos.x){
                //top
                if( pos.y < trigger.y ){
                    drag = i+1;
                    trigger_pos = glm::vec2(t->pos.x, 0);
                    anchor_pos = glm::vec2(t->pos.x+t->size.x, 0);
                    break;
                }
                //bottom
                if(pos.y + trigger.y > t->pos.y + t->size.y){
                    drag = i+1;
                    trigger_pos = glm::vec2(t->pos.x, t->pos.y + t->size.y);
                    anchor_pos = glm::vec2(t->pos.x+t->size.x, t->pos.y + t->size.y);
                    break;
                }
                //handle left edge
                if(dir == 0 && i > 0){
                    printf("left grab\n");
                    drag = i;
                    trigger_pos = glm::vec2(t->pos.x, 0);
                    anchor_pos = glm::vec2(t->pos.x+t->size.x, 0);
                    created = true;
                    break;
                }
            }
            else if(dir ==  1){
                //top edge (min y)
                if(pos.y - trigger.y < t->pos.y && pos.y < t->pos.y){
                    printf("top grab\n");
                    drag = i;
                    trigger_pos = glm::vec2(0, t->pos.y);
                    anchor_pos = glm::vec2(0, t->pos.y+t->size.y);
                    created = true;
                    break;
                }
                //bottom edge (max y)
                else if(pos.y + trigger.y > t->pos.y + t->size.y && pos.y < t->pos.y + t->size.y){
                    printf("bottom grab\n");
                    drag = i+1;
                    trigger_pos = glm::vec2(g->in[i+1]->pos.x+g->in[i+1]->size.x, 0);
                    anchor_pos = trigger_pos;
                    created = true;
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
        for(int i=0;i<2;i++){
            if(!dir_unset() && dir != i){
                continue;
            }
            Brick* br = bricks[drag-1];
            if(!created && pos[i] > br->tile->pos[i] + trigger[i]*2 && pos[i] + trigger[i]*2 < br->tile->pos[i] + br->tile->size[i] ){
                if(dir_unset()){
                    dir = i;
                }
                if(dir == i){
                    Brick* b = new_empty();
                    b->tile->pos[i] = anchor_pos[i];
                    insert(b, drag);
                    created = true;
                }
            }
            if(created && dir == i){
                bricks[drag-1]->tile->size[i] = pos[i] - bricks[drag-1]->tile->pos[i];
                bricks[drag]->tile->size[i] = anchor_pos[i] - pos[i];
                bricks[drag]->tile->pos[i] = pos[i];

                if(pos[i] > anchor_pos[i] - trigger[i] || pos[i] < bricks[drag-1]->tile->pos[i] + trigger[i] && bricks.size() > 1){
                    bricks[drag-1]->tile->size[i] += bricks[drag]->tile->size[i];
                    remove(drag);
                    //TODO this is definitely a memory leak
                    /*if(bricks.size() == 1){
                        dir = -1;
                        drag = 0;
                    }*/
                    created = false;
                    break;
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