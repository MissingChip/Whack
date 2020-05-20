
#include "brick.h"
#include "group.h"
#include <cstdio>

void Brick::attach(Tile* t){
    tile = t;
}
void Brick::forward_all(bool f){
    forward_outclick = f;
    forward_outmouse = f;
    forward_outrelease = f;
}
bool Brick::is_inside(glm::vec2 pos){
    return pos[0] > tile->pos[0] && pos[0] < tile->pos[0] + tile->size[0] && pos[1] > tile->pos[1] && pos[1] < tile->pos[1] + tile->size[1];
}

void Brick::clicked(glm::vec2 pos, int button){
    if(on_click) on_click(pos, button);
    for(Brick* p : bricks){
        glm::vec2& pp = p->tile->pos; //page pos
        glm::vec2& ps = p->tile->size;//page size
        if((pp.x < pos.x && pp.x + ps.x > pos.x && 
                pp.y < pos.y && pp.y + ps.y > pos.y)
                || forward_outclick){
            p->clicked(pos-pp, button);
        }
    }
}
void Brick::mouse(glm::vec2 pos){
    if(on_mouse) on_mouse(pos);
    for(Brick* p : bricks){
        glm::vec2& pp = p->tile->pos; //page pos
        glm::vec2& ps = p->tile->size;//page size
        if((pp.x < pos.x && pp.x + ps.x > pos.x && 
                pp.y < pos.y && pp.y + ps.y > pos.y)
                || forward_outmouse){
            p->mouse(pos-pp);
        }
    }
}
void Brick::released(glm::vec2 pos, int button){
    if(on_release) on_release(pos, button);
    for(Brick* p : bricks){
        glm::vec2& pp = p->tile->pos; //page pos
        glm::vec2& ps = p->tile->size;//page size
        if((pp.x < pos.x && pp.x + ps.x > pos.x && 
                pp.y < pos.y && pp.y + ps.y > pos.y)
                || forward_outrelease){
            p->released(pos-pp, button);
        }
    }
}

void Brick::update(){
    Group* g = dynamic_cast<Group*>(tile);
    if(g){
        /*if(bricks.size() != g->in.size()){
            printf("Group size mismatch\n");
        }*/
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
    if(Group* g = dynamic_cast<Group*>(tile)){
        g->remove(p->tile);
    }
    for(int i=0;i<bricks.size();i++){
        if(bricks[i] == p){
            bricks.erase(bricks.begin()+i);
            return;
        }
    }
}
void Brick::remove(uint index){
    if(Group* g = dynamic_cast<Group*>(tile)){
        g->remove(bricks[index]->tile);
    }
    bricks.erase(bricks.begin()+index);
}
int Brick::idx_of(Brick* p){
    for(int i=0;i<bricks.size();i++){
        if(bricks[i] == p){
            return i;
        }
    }
    return -1;
}
void Brick::replace(Brick* b1, Brick* b2){
    replace(idx_of(b1), b2);
}
void Brick::replace(uint i, Brick* b2){
    if(Group* g = dynamic_cast<Group*>(tile)){
        g->replace(bricks[i]->tile, b2->tile);
    }
    bricks[i] = b2;
}
int Brick::interact(const glm::vec2& pos){
    return 0;
}
int Brick::check_interact(const glm::vec2& pos){
    for(Brick* b : bricks){
        int a = b->interact(pos - b->tile->pos);
        if(a) return a;
    }
    return 0;
}