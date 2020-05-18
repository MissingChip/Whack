
#include "brick.h"
#include "group.h"

void Brick::attach(Tile* t){
    tile = t;
}

void Brick::clicked(glm::vec2 pos, int button){
    if(on_click) on_click(pos, button);
    for(Brick* p : bricks){
        glm::vec2& pp = p->tile->pos; //page pos
        glm::vec2& ps = p->tile->size;//page size
        if(pp.x < pos.x && pp.x + ps.x > pos.x && 
                pp.y < pos.y && pp.y + ps.y > pos.y){
            p->clicked(pos-pp, button);
        }
    }
}
void Brick::mouse(glm::vec2 pos){
    if(on_mouse) on_mouse(pos);
    for(Brick* p : bricks){
        glm::vec2& pp = p->tile->pos; //page pos
        glm::vec2& ps = p->tile->size;//page size
        if(pp.x < pos.x && pp.x + ps.x > pos.x && 
                pp.y < pos.y && pp.y + ps.y > pos.y){
            p->mouse(pos-pp);
        }
    }
}
void Brick::released(glm::vec2 pos, int button){
    if(on_release) on_release(pos, button);
    for(Brick* p : bricks){
        glm::vec2& pp = p->tile->pos; //page pos
        glm::vec2& ps = p->tile->size;//page size
        if(pp.x < pos.x && pp.x + ps.x > pos.x && 
                pp.y < pos.y && pp.y + ps.y > pos.y){
            p->released(pos-pp, button);
        }
    }
}

void Brick::update(){
    Group* g = dynamic_cast<Group*>(tile);
    if(g){
        glm::vec2 size = g->size;
        for(int i=0;i<update_threshold;i++){
            g->update();
            if(g->size == size){
                break;
            }
            size = g->size;
        }
    }
    for(Brick* p : bricks){
        p->update();
    }
    if(g){
        glm::vec2 size = g->size;
        for(int i=0;i<update_threshold;i++){
            g->update();
            if(g->size == size){
                break;
            }
            size = g->size;
        }
    }
}
/*
void Coat::shout(){
    Group* g = dynamic_cast<Group*>(tile);
    if(g){
        glm::vec2 size = g->size;
        for(int i=0;i<update_threshold;i++){
            g->update();
            if(g->size == size){
                break;
            }
            size = g->size;
        }
    }

}*/

void Brick::add(Brick* p){
    bricks.push_back(p);
    if(Group* g = dynamic_cast<Group*>(tile)){
        g->add(p->tile);
    }
}
void Brick::insert(Brick* p, int index){
    if(index<0) index=bricks.size()+index;
    bricks.insert(bricks.begin()+index,p);
    if(Group* g = dynamic_cast<Group*>(tile)){
        g->insert(p->tile, index);
    }
}
void Brick::remove(Brick* p){
    for(int i=0;i<bricks.size();i++){
        if(bricks[i] == p){
            bricks.erase(bricks.begin()+i);
            return;
        }
    }
}
int Brick::idx_of(Brick* p){
    for(int i=0;i<bricks.size();i++){
        if(bricks[i] == p){
            return i;
        }
    }
    return -1;
}