
#include <vector>

#include "rowmod.h"

using namespace std;

void RowMod::apply(Group* g){
    bool& o = direction;
    vector<Tile*>& in = g->in;
    float at = 0;
    for(int i=0;i<in.size();i++){
        Tile* c = in[i];
        c->pos[o] = g->pos[o] + at;
        at += c->size[o]+spacing;
    }
    g->size[o] = at-spacing;
}