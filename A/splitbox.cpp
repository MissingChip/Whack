

#include "splitbox.h"

void SplitBox::click(double x, double y){
    clicked.x = x;
    clicked.y = y;
    double lin;
    if(horizontal){
        lin = x;
    }else{
        lin = y;
    }
    for(int i=0; i<handles.size();i++){
        if(handles[i]-handle_width < lin && handles[i]+handle_width > lin){
            grabbed = lin;
            grabbed_handle = i;
        }
    }
}
void SplitBox::hover(double x, double y){
    clicked.x = x;
    clicked.y = y;
    double lin;
    if(horizontal){
        lin = x;
    }else{
        lin = y;
    }
    if(grabbed_handle > 0){
        handles[grabbed_handle] = lin-grabbed;
    }
}
void SplitBox::release(double x, double y){
    grabbed_handle = -1;
}