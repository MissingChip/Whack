#include "row.h"
#include "group.h"

Row::Row(){
    tile = &group;
    group.add(&alignmod);
    group.add(&rowmod);
}