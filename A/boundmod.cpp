
//#include <math.h>
#include "boundmod.h"

using namespace std;

void BoundMod::apply(Group* g){
    float min_x;
    float max_x;
    float min_y;
    float max_y;
    for(Tile* t : g->in){
        min_x = min(min_x, t->pos.x);
        min_y = min(min_y, t->pos.y);
        max_x = max(max_x, t->pos.x+t->size.x);
        max_y = max(max_y, t->pos.y+t->size.y);
    }
    Vec2 dif = Vec2(min_x - left, min_y - top);
    for(Tile* t : g->in){
        t->pos -= dif;
    }
    if(force_size){
        g->size.x = left + right + max_x - min_x;
        g->size.y = top + bottom + max_y - min_y;
    }
    else{
        g->size.x = min(g->size.x, left + right + max_x - min_x);
        g->size.y = min(g->size.y, top + bottom + max_y - min_y);
    }
}