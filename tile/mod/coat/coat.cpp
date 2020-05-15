
#include "coat.h"
#include "group.h"

void Coat::attach(Tile* t){
    tile = t;
}

void Coat::clicked(glm::vec2 pos){
    if(on_click) on_click(pos);
    for(Coat* p : pages){
        glm::vec2& pp = p->tile->pos; //page pos
        glm::vec2& ps = p->tile->size;//page size
        if(pp.x < pos.x && pp.x + ps.x > pos.x && 
                pp.y < pos.y && pp.y + ps.y > pos.y){
            p->clicked(pos-pp);
        }
        //p->clicked_off(pos-pp);
    }
}

void Coat::update(){
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
    for(Coat* p : pages){
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

void Coat::add(Coat* p){
    pages.push_back(p);
    if(Group* g = dynamic_cast<Group*>(tile)){
        g->add(p->tile);
    }
}
void Coat::insert(Coat* p, int index){
    if(index<0) index=pages.size()+index;
    pages.insert(pages.begin()+index,p);
}
void Coat::remove(Coat* p){
    for(int i=0;i<pages.size();i++){
        if(pages[i] == p){
            pages.erase(pages.begin()+i);
            return;
        }
    }
}
int Coat::idx_of(Coat* p){
    for(int i=0;i<pages.size();i++){
        if(pages[i] == p){
            return i;
        }
    }
    return -1;
}