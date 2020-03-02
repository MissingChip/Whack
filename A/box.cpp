
//#include "wmath.h"
#include "box.h"

/*Box::~Box(){
    for(int i=0;i<children.size();i++){
        delete children[i];
    }
}*/

void Box::add(Widget* w){
    children.push_back(w);
    w->reparent(this);
}
Widget* Box::child(int i){
    if(i < children.size()){
        return children[i];
    }
    return nullptr;
}