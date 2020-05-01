#include "group.h"
#include "modifier.h"
#include "mods.h"

#include <cstdio>

void Group::update() {
    for(Modifier* m : mods){
        m->apply(this);
    }
}
void Group::update_all() {
    for(Tile* t : in){
        if(Group* g = dynamic_cast<Group*>(t)){
            g->update_all();
        }
    }
    for(Modifier* m : mods){
        m->apply(this);
    }
}
void Group::add(Tile* t){
    in.push_back(t);
    t->parent = this;
}
void Group::add(Modifier* m){
    mods.push_back(m);
    m->track(this);
}

Group::~Group(){
    for(Modifier* mod : mods){
        mod->forget(this);
    }
}