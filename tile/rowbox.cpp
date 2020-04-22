
#include "rowbox.h"

RowBox::RowBox(){
    init();
}

RowBox::~RowBox(){
}

void RowBox::set_direction(bool vertical){
    rowmod.direction = vertical;
    if(vertical) alignmod.anchor = anchors::left;
    else alignmod.anchor = anchors::top;
}

void RowBox::set_align(int anchor){
    alignmod.anchor = anchor;
}

void RowBox::init(){
    add(&alignmod);
    add(&rowmod);
}