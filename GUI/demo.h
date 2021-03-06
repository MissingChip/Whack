#pragma once

#include "group.h"
#include "mods.h"

#include <vector>

class MenuBar : public Group {
public:
    MenuBar();
    RowMod rowmod = RowMod(0);
    StretchMod stretchmod = StretchMod(anchors::vertical);
    std::vector<Tile> opts;
};
class Inner : public Group {
public:
    Inner();
    RowMod rowmod = RowMod(0);
    StretchMod stretchmod = StretchMod(anchors::vertical);
    FillMod fillmod = FillMod(0);
    Group ag = Group(200, 0);
    Group bg;
};
class Margins : public Group {
public:
    Margins();
    //StretchMod stretchmod = StretchMod(anchors::all);
    MarginMod margins = MarginMod(10, 20);
    Inner i = Inner();
};

class Demo : public Group {
public:
    //Tracker<Tile> t;
    MenuBar menu;
    Margins m;
    RowMod rowmod = RowMod(1);
    StretchMod stretchmod = StretchMod(anchors::horizontal);
    FillMod fillmod = FillMod(1);
    virtual void add(Tile* tile);
    virtual void add(Modifier* mod){Group::add(mod);};
    virtual void update_all();
    Demo();
    ~Demo();
};

inline MenuBar::MenuBar(){
    add(&rowmod);
    add(&stretchmod);
    for(int i=0;i<5;i++){
        opts.push_back(Tile(0,0,60,0));
    }
    
    for(int i=0;i<5;i++){
        add(&(opts[i]));
    }
    size.y = 24;
}
inline Inner::Inner(){
    add(&rowmod);
    add(&stretchmod);
    add(&fillmod);
    add(&ag);
    add(&bg);
}
inline Margins::Margins(){
    //add(&stretchmod);
    add(&margins);
    i.size=glm::vec2(10000, 10000);
    add(&i);
}

inline void Demo::add(Tile* tile){
    if(tile->parent){
        //parent->remove(tile);
    }
    tile->id = in.size();
    Group::add(tile);
}

inline Demo::Demo(){
    add(&rowmod);
    add(&stretchmod);
    add(&fillmod);
    add(&menu);
    add(&m);
}

inline void Demo::update_all(){
    Group::update_all();
    //printf("%f %f\n", t[2]->size.x, t[2]->size.y);
}

inline Demo::~Demo(){
    //int i = 1;
    //while(t[i]){
    //    delete t.remove(i);
    //    i++;
    //}
}