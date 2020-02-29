
#include "fixbox.h"

#include <stdio.h>

void FixBox::update(){
    for(int i=0; i<children.size();i++){
        Widget* child = children[i];
        Pos offset;
        uint t = anchors[i].type;
        if(t == none){
            t = bottom_left;
        }
        if(t == RIGHT || t == LEFT){
            offset.y = -child->get_h()/2;
        }
        if(t == TOP || t == BOTTOM){
            offset.x = -child->get_w()/2;
        }
        if(t | RIGHT){
            offset.x = -child->get_w();
        }
        if(t | TOP){
            offset.y = -child->get_h();
        }
        child->set_pos(offset);
    }
}

void FixBox::set_anchor(Widget& w, const Anchor& a){
    for(int i=0; i<children.size();i++){
        if(w.id == children[i]->id){
            anchors[i] = a;
            return;
        }
    }
    fprintf(stderr, "Widget %u not found\n", w.id);
}
void FixBox::set_anchor(Widget* w, const Anchor* a){
    set_anchor(*w, *a);
}