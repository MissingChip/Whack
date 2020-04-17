
#include <cstdio>

#include "A/rowbox.h"
#include "A/stretchmod.h"

int main(){
    Tile t;
    Tile t2;
    RowBox m;
    StretchMod s;
    m.add(&s);
    m.size.x = 100;
    m.size.y = 100;
    t.size.y = 20;
    t2.size.y = 30;
    t.pos.x = 20;
    t.size.x = 20;
    t2.size.x = 30;
    m.add(&t);
    m.add(&t2);
    printf("%2f, %2f\n", t.size.x, t.size.y);
    m.update();
    printf("pos (%2f, %2f)\tsize (%2f, %2f)\n", t.pos.x, t.pos.y, t.size.x, t.size.y);
    printf("pos (%2f, %2f)\tsize (%2f, %2f)\n", t2.pos.x, t2.pos.y, t2.size.x, t2.size.y);
}