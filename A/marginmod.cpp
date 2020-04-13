
#include "marginmod.h"

void MarginMod::apply(Group* g){
    for(Tile* t : g->in){
        if(t->pos.x + t->size.x > g->size.x){
            t->pos.x = g->size.x - t->size.x;
        }
        if(t->pos.y + t->size.y > g->size.y){
            t->pos.y = g->size.y - t->size.y;
        }
        if(t->pos.x == 0) t->pos.x = 0;
        if(t->pos.y == 0) t->pos.y = 0;
    }
}