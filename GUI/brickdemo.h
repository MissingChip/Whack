#pragma once
#include "group.h"
#include "mods.h"
#include "../tile/mod/brick/brick.h"
#include "../tile/mod/brick/menubar.h"
#include "../tile/mod/brick/row.h"

#include <vector>

using namespace std;

void menu1click(glm::vec2 pos){
    printf("aaa\n");
}

class BrickDemo : public Row {
public:
    BrickDemo();

    MenuBar menu;
    Row inner;
    StretchMod stretchmod = StretchMod(anchors::horizontal);
    FillMod fillmod;

    virtual void update();
};

inline BrickDemo::BrickDemo() : Row() {
    add(&menu);
    add(&inner);
    group.add(&fillmod); 
    group.add(&stretchmod);
    menu.bricks[0]->on_click = menu1click;
}

void BrickDemo::update() {
    Row::update();
    //printf("%f %f\n", inner.tile->size.x, inner.tile->size.y);
}