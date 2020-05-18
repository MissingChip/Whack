#pragma once
#include "group.h"
#include "mods.h"
#include "../tile/mod/brick/brick.h"
#include "../tile/mod/brick/menubar.h"
#include "../tile/mod/brick/row.h"
#include "../tile/mod/brick/fold.h"

#include <vector>

using namespace std;

void menu1click(glm::vec2 pos, int b){
    printf("aaa\n");
}
void menu1release(glm::vec2 pos, int b){
    printf("bbb\n");
}

class BrickDemo : public Row {
public:
    BrickDemo();

    MenuBar menu;
    Row inner;
    Fold fold;
    StretchMod stretchmod = StretchMod(anchors::horizontal);
    FillMod fillmod;

    virtual void update();
};

inline BrickDemo::BrickDemo() : Row() {
    add(&menu);
    add(&fold);
    group.add(&fillmod); 
    group.add(&stretchmod);
    menu.bricks[1]->on_click = menu1click;
    menu.bricks[1]->on_release = menu1release;
}

void BrickDemo::update() {
    Row::update();
    //printf("%f %f\n", inner.tile->size.x, inner.tile->size.y);
}