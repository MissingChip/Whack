
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
        if(a & right) {
            t->pos.x = (size.x-t->size.x)/2;
        } else {
            t->pos.x = 0;
        }
    } else if(a & right) {
        t->pos.x = size.x-t->size.x;
    }
    if(a & top) {
        if(a & bottom) {
            t->pos.y = (size.y-t->size.y)/2;
        } else {
            t->pos.y = 0;
        }
    } else if(a & bottom) {
        t->pos.y = size.y-t->size.y;
    }
}