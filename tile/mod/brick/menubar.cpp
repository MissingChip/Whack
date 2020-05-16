
#include "menubar.h"
#include "label.h"

MenuBar::MenuBar(int numopts){
    Group* g = new Group();
    tile = g;
    g->add(&rowmod);
    g->add(&stretchmod);
    for(int i=0;i<numopts;i++){
        add(new Label());
    }
    g->size.y = 24;
}

MenuBar::~MenuBar(){
    for(Brick* o : bricks){
        delete o;
    }
}