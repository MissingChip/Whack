
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
                if(Group* g = dynamic_cast<Group*>(tile)){
                    printf("%lu\n", g->in.size());
                    Tile* t = g->in[0];
                    printf("%f %f %f %f\n", t->pos.x, t->pos.y, t->size.x, t->size.y);
                }
                //printf("%d\n", bricks[drag-1]->tile->size.x );
                
                //printf("cccc\n");
                bricks[drag-1]->tile->size.x = pos.x - bricks[drag-1]->tile->pos.x;
                bricks[drag]->tile->size.x = trigger_pos.x - pos.x;
                bricks[drag]->tile->pos.x = pos.x;
            }
        }
    }
}

void Fold::released(glm::vec2 pos, int button){
    drag = 0;
    created = false;
}

Brick* Fold::new_empty(){
    Brick* b = new Brick();
    b->tile = new Tile();
    b->tile->size.y = tile->size.y;
    return b;
}
bool Fold::dir_unset(){
    return dir == -1;
}