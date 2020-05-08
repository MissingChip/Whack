
#include "marginmod.h"
#include <cstdio>

MarginMod::MarginMod(float ud, float lr){
    top = bottom = ud;
    left = right = lr;
}
MarginMod::MarginMod(float t, float r, float b, float l){
    top = t;
    right = r;
    bottom = b;
    left = l;
}

void MarginMod::apply(Group* g){
    glm::vec2 size = glm::vec2(g->size.x - left - right, g->size.y - top - bottom);
    for(Tile* t : g->in){
        if(fill){
            t->size = size;
            t->pos.x = left;
            t->pos.y = top;
            continue;
        }
        //printf("A%f %f, %f %f, %f %f %f %f\n", t->size.x, t->size.y, t->pos.x, t->pos.y, top, bottom, left, right);
        if(t->size.x > g->size.x - left - right){
            t->size.x = g->size.x - left - right;
        //printf("BA%f %f, %f %f\n", t->size.x, t->size.y, t->pos.x, t->pos.y);
        }
        if(t->size.y > g->size.y - top - bottom){
            t->size.y = g->size.y - top - bottom;
        //printf("BB%f %f, %f %f\n", t->size.x, t->size.y, t->pos.x, t->pos.y);
        }
        if(t->pos.x + t->size.x > g->size.x - right){
            t->pos.x = g->size.x - t->size.x - right;
        //printf("BC%f %f, %f %f\n", t->size.x, t->size.y, t->pos.x, t->pos.y);
        }
        if(t->pos.x < left){
            t->pos.x = left;
        //printf("BD%f %f, %f %f\n", t->size.x, t->size.y, t->pos.x, t->pos.y);
        }
        if(t->pos.y + t->size.y > g->size.y - bottom){
            t->pos.y = g->size.y - t->size.y - bottom;
        //printf("BE%f %f, %f %f\n", t->size.x, t->size.y, t->pos.x, t->pos.y);
        }
        if(t->pos.y < top){
            t->pos.y = top;
        //printf("BF%f %f, %f %f\n", t->size.x, t->size.y, t->pos.x, t->pos.y);
        }
        //printf("B%f %f, %f %f, %f %f\n", t->size.x, t->size.y, t->pos.x, t->pos.y, g->size.x, g->size.y);
        /* t->pos = glm::vec2(0,0);
        t->size = glm::vec2(100,100); */
    }
}