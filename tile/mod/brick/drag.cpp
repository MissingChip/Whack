
#include "drag.h"
#include "group.h"

#include <stdio.h>

Drag::Drag(){
    tile = new Group;
}
Drag::~Drag(){
    delete tile;
}


void Drag::clicked(glm::vec2 pos, int button){
    bool interacted = false;
    if(!drag){
        for(int i=0;i<bricks.size();i++){
            if(bricks[i]->tile->contains(pos)){
                drag = i+1;
                trigger_pos = bricks[i]->tile->pos-pos;
                interacted = true;
                break;
            }
        }
    }
    if(!interacted){
        Brick::clicked(pos, button);
    }
}

void Drag::mouse(glm::vec2 pos){
    //printf("moused fold %f %f\n", pos.x, pos.y);
    if(drag){
        Brick* br = bricks[drag-1];
        br->set_pos(pos+trigger_pos);
        glm::vec2 pos = br->get_pos();
        glm::vec2 pos2 = pos + br->get_size(); 
        glm::vec2 size = get_size(); 
        if(pos.x < 0) br->set_x(0);
        if(pos.y < 0) br->set_y(0);
        if(pos2.x > size.x) br->set_x(size.x - br->get_w());
        if(pos2.y > size.y) br->set_y(size.y - br->get_h());

    }
}

void Drag::released(glm::vec2 pos, int button){
    if(drag){
        drag = 0;
    }
}
