
//#include "wmath.h"
#include "box.h"

using namespace std;

void Box::add(Tile* w){
    children.push_back(w);
    w->reparent(this);
}
Tile* Box::child(int i){
    if(i < children.size()){
        return children[i];
    }
    return nullptr;
}