
#include "stretchmod.h"

using namespace anchors;



void StretchMod::apply(Group* g){
    for(Tile* t : g->in){
        if(direction & top){
            float p = t->pos.y;
            t->pos.y = 0;
            t->size.y += p;
        }
        if(direction & left){
            float p = t->pos.x;
            t->pos.x = 0;
            t->size.x += p;
        }
        if(direction & bottom){
            t->size.y = g->pos.y-t->pos.y;
        }
        if(direction & right){
            t->size.x = g->pos.x-t->pos.x;
        }
    }
}