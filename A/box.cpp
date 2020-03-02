
//#include "wmath.h"
#include "box.h"

using namespace std;

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
string Box::to_string(){
    string o = "B:[";
    int i;
    if(children.size() > 0){
        for(i = 0; i < children.size()-1; i++){
            o += children[i]->to_string() + ", ";
        }
        o += children[i]->to_string();
    }
    o.push_back(']');
    return o;
}