
//#include <math.h>
#include "boundmod.h"

using namespace std;

void BoundMod::apply(Group* g){
    if(g->in.size() == 0) return;
    glm::vec2& s = g->in[0]->pos;
    float min_x = s.x;
    float max_x = s.x;
    float min_y = s.y;
    float max_y = s.y;
    for(Tile* t : g->in){
        min_x = min(min_x, t->pos.x);
        min_y = min(min_y, t->pos.y);
        max_x = max(max_x, t->pos.x+t->size.x);
        max_y = max(max_y, t->pos.y+t->size.y);
    }
    glm::vec2 dif = glm::vec2(min_x - left, min_y - top);
    for(Tile* t : g->in){
        t->pos -= dif;
    }
    if(force_size){
        if(bind_x) g->size.x = left + right + max_x - min_x;
        if(bind_y) g->size.y = top + bottom + max_y - min_y;
    }
    else{
        if(bind_x)g->size.x = min(g->size.x, left + right + max_x - min_x);
        if(bind_y)g->size.y = min(g->size.y, top + bottom + max_y - min_y);
    }
}