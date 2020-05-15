
#include "group.h"
#include "mods.h"
#include "../tile/mod/coat/coat.h"
#include "../tile/mod/coat/menubar.h"
#include "../tile/mod/coat/row.h"

#include <vector>

using namespace std;

class PageDemo : public Row {
public:
    PageDemo();

    MenuBar menu;
    Row inner;
    StretchMod stretchmod = StretchMod(anchors::horizontal);
    FillMod fillmod;

    virtual void update();
};

inline PageDemo::PageDemo() : Row() {
    add(&menu);
    add(&inner);
    group.add(&fillmod); 
    group.add(&stretchmod); 
}

void PageDemo::update() {
    Row::update();
    //printf("%f %f\n", inner.tile->size.x, inner.tile->size.y);
}