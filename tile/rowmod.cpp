
#include <vector>

#include "rowmod.h"

using namespace std;

void RowMod::apply(Group* g){
    bool& o = direction;
    vector<Tile*>& in = g->in;
    float at = 0;
    for(int i=0;i<in.size();i++){
        Tile* c = in[i];
        c->pos[o] = at;
        at += c->size[o]+spacing;
    }
    if(resize_on_update){
        g->size[o] = at-spacing;
    }
}