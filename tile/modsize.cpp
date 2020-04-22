#include "modsize.h"

using namespace std;

void MinSizeMod::apply(Group* g){
    g->size.x = max(size.x, g->size.x);
    g->size.y = max(size.y, g->size.y);
}
void MaxSizeMod::apply(Group* g){
    g->size.x = min(size.x, g->size.x);
    g->size.y = min(size.y, g->size.y);
}