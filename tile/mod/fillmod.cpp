#include "fillmod.h"

#include <cstdio>

void FillMod::apply(Group* g){
    int m = g->in.size();
    if(m == 0){
        return;
    }
    int idx = index<0 ? m+index : index;
    glm::vec2 space = g->size;
    for(int i=0;i<m;i++){
        if(i == idx) continue;
        space -= g->in[i]->size;
    }
    float adj;
    if(direction==0 && space.x > 0){
        adj = space.x - g->in[idx]->size.x;
        g->in[idx]->size.x = space.x;
    }
    else if(direction==1 && space.y > 0){
        adj = space.y - g->in[idx]->size.y;
        g->in[idx]->size.y = space.y;
    }
    else{
        return;
    }
    for(int i=idx+1;i<m;i++){
        g->in[i]->pos[direction] += adj;
    }
}