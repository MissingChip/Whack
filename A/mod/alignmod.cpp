
#include <vector>

#include "alignmod.h"


using namespace std;
using namespace anchors;

void AlignMod::apply(Group* g){
    for(Tile* t : g->in){
        align_tile(t, g);
    }

}
void AlignMod::align_tile(Tile* t, Group* g){
    int& a = anchor;
    Vec2& pos = g->pos;
    Vec2& size = g->size;
    
    if(a & left){
        t->pos.x = pos.x;
    }else if(a & right){
        t->pos.x = pos.x+size.x-t->size.x;
    }
    if(a & top){
        t->pos.y = pos.y;
    }else if(a & bottom){
        t->pos.y = pos.y+size.y-t->size.y;
    }
}