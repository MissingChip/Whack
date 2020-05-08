
#include "page.h"
#include "group.h"

Page* Page::clicked(glm::vec2 pos){
    if(Group* g = dynamic_cast<Group*>(tile)){
        for(Tile* t : g->in){
            if(t->pos.x < pos.x && t->pos.x + t->size.x > pos.x && 
                    t->pos.y < pos.y && t->pos.y + t->size.y > pos.y){
                return ((Page*)t->data)->clicked(pos-(glm::vec2)(t->pos));
            }
        }
    }
    return this;
}