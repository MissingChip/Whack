
#include <cstdio>

#include "rowbox.h"

int main(){
    Tile t;
    Tile t2;
    RowBox m;
    m.size.x = 100;
    m.size.y = 100;
    t.size.y = 20;
    t2.size.y = 30;
    t.size.x = 20;
    t2.size.x = 30;
    m.add(&t);
    m.add(&t2);
    printf("%2f, %2f\n", t.size.x, t.size.y);
    m.update();
    printf("%2f, %2f\t%2f, %2f\n", t.pos.x, t.pos.y, t.size.x, t.size.y);
    printf("%2f, %2f\t%2f, %2f\n", t2.pos.x, t2.pos.y, t2.size.x, t2.size.y);
}