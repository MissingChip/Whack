
#include "rowbox.h"

RowBox::RowBox(){;
    add(alignmod = new AlignMod());
    add(rowmod = new RowMod());
}

RowBox::~RowBox(){
    if(alignmod){
        delete alignmod;
        alignmod = nullptr;
    }
    if(rowmod){
        delete rowmod;
        rowmod = nullptr;
    }
}

void RowBox::set_direction(bool horizontal){
    rowmod->direction = horizontal;
}

void RowBox::set_align(int anchor){
    alignmod->anchor = anchor;
}