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
    if(t->parent) t->parent->remove(t);
    t->parent = this;
}
void Group::add(Modifier* m){
    mods.push_back(m);
}

void Group::remove(Tile* t){
    for(int i=0;i<in.size();i++){
        if(in[i] == t){
            in.erase(in.begin()+i);
            return;
        }
    }
}
void Group::remove(Modifier* m){
    for(int i=0;i<mods.size();i++){
        if(mods[i] == m){
            mods.erase(mods.begin()+i);
            return;
        }
    }
}

Group::~Group(){
}