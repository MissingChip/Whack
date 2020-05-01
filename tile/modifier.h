#pragma once

#include <cstdio>
#include <vector>

#include "tile.h"
#include "group.h"

class Modifier {
public:
    uint groups = 1;

    virtual void apply(Group*) = 0;
    virtual void track(Group*);
    virtual void forget(Group*);
    virtual void update(){};
};

inline void Modifier::track(Group* g) {
    if(groups) groups++;
}
inline void Modifier::forget(Group* g) {
    if(groups == 2){
        //printf("oof1\n");
        delete this;
        //printf("oof2\n");
    }
    groups--;
}