
#include <cstdio>

#include "mod/stretchmod.h"

int main(){
    Group g;
    Tile t;
    StretchMod m;
    m.direction = anchors::bottom;
    g.add(&t);
    g.add(&m);
    g.size.x = 100;
    g.size.y = 100;
    printf("%2f, %2f\n", t.size.x, t.size.y);
    g.update();
    printf("%2f, %2f\n", t.size.x, t.size.y);
}