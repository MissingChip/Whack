
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

    Row inner;
    MenuBar menu;
    FillMod fillmod;
};

inline PageDemo::PageDemo() : Row() {
    add(&menu);
    add(&inner);
    group.add(&fillmod); 
}