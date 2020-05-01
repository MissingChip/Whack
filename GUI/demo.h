#pragma once

#include "group.h"
#include "mods.h"
#include "tracker.h"

class Demo : public Group {
public:
    Tracker<Tile> t;
    virtual void add(Tile* tile);
    virtual void add(Modifier* mod){Group::add(mod);};
    virtual void remove(uint id);
    virtual void remove(Tile* tile);
    virtual void update_all();
    Demo();
    ~Demo();
};

class Inner : public Group {
    
};

inline void Demo::add(Tile* tile){
    Group::add(tile);
    tile->id = t.add(tile);
}

inline void Demo::remove(Tile* tile){
    t.remove(tile->id);
    delete tile;
}

inline void Demo::remove(uint id){
    delete t.remove(id);
}

inline Demo::Demo(){
    Group* m = new Group;
    m->size.y = 30;
    add(m);
    Group* p = new Group();
    p->add(new RowMod(0));
    m = new Group();
    m->size.x = 200;
    p->add(m);
    m = new Inner();
    p->add(m);
    p->add(new StretchMod(anchors::vertical));
    p->add(new FillMod(0));
    p->size.y = 200;
    add(p);
    add(new RowMod(1));
    add(new StretchMod(anchors::horizontal));
    FillMod* a = new FillMod(1);
    add(new FillMod(1));
}

inline void Demo::update_all(){
    Group::update_all();
    //printf("%f %f\n", t[2]->size.x, t[2]->size.y);
}

inline Demo::~Demo(){
    int i = 1;
    while(t[i]){
        delete t.remove(i);
    }
}