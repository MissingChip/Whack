
#include "menubar.h"
#include "label.h"

MenuBar::MenuBar(int numopts){
    Group* g = new Group();
    tile = g;
    g->add(&rowmod);
    g->add(&stretchmod);
    for(int i=0;i<numopts;i++){
        opts.push_back(new Label());
    }
    
    for(int i=0;i<numopts;i++){
        g->add(opts[i]->tile);
    }
    g->size.y = 24;
}

MenuBar::~MenuBar(){
    for(Coat* o : opts){
        delete o;
    }
}