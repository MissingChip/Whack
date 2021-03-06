
#include <cstdio>

#include "fold.h"
#include "group.h"

enum interact_opts{
    none,
    edge,
    corner
};

glm::vec2 Fold::trigger = glm::vec2(12, 10);

Fold::Fold(){
    tile = new Group;
    Brick* b = current_empty();
    add(b);
    forward_nonclick(true);
}
Fold::Fold(int opt){
    tile = new Group;
    forward_all();
}
Fold::~Fold(){
    delete tile;
}

void Fold::clicked(glm::vec2 pos, int button){
    pmouse_pos = pos;
    bool interacted = false;
    if(!drag){
        if(bricks.size() == 1){
            dir = -1;
        }
        Group* g = static_cast<Group*>(tile);
        for(int i=0;i<g->in.size();i++){
            Tile* t = g->in[i];
            int a[2] {0,0};
            int dout = -2;
            //check both directions
            for(int d=0;d<2;d++){
                //close edge
                if(pos[d] - trigger[d] < t->pos[d] && pos[d] >= t->pos[d] - 0.05){
                    a[d] = 1;
                }
                //far edge
                else if(pos[d] + trigger[d] > t->pos[d] + t->size[d] && pos[d] <= t->pos[d] + t->size[d]){
                    a[d] = 2;
                }
                //set dragging info
                if(a[d]){
                    trigger_pos[d] = t->pos[d];
                    anchor_pos[d] = t->pos[d] + t->size[d];
                    dout = d;
                }
            }
            Fold* f = dynamic_cast<Fold*>(bricks[i]);
            //if f is not a fold, if f is a fold continue only if it is not to be interacted with
            if(!(f) || !(f->interact(pos-f->tile->pos))){
                //corner
                if(a[0] && a[1]){
                    created = false;
                    drag = i+1;
                    interacted = true;
                    break;
                }
                //edge
                else if (dout == dir){
                    if( int b = a[0] | a[1] ){
                        created = true;
                        drag = 0;
                        if(i < g->in.size()-1 && b == 2){
                            trigger_pos = t->pos;
                            anchor_pos = g->in[i+1]->pos + g->in[i+1]->size;
                            drag = i+1;
                            interacted = true;
                        }
                        if(i > 0 && b == 1){
                            trigger_pos = g->in[i-1]->pos;
                            anchor_pos = t->pos + t->size;
                            drag = i;
                            interacted = true;
                        }
                        break;
                    }
                }
            }
        }
    }
    if(!interacted){
        Brick::clicked(pos, button);
    }
}

void Fold::mouse(glm::vec2 pos){
    //printf("moused fold %f %f\n", pos.x, pos.y);
    if(drag){
        Brick* br = bricks[drag-1];
        for(int d=0;d<2;d++){
            //slide out and create a brick
            if(!created && pos[d] - trigger[d]*2 > br->tile->pos[d] && pos[d] + trigger[d]*2 < br->tile->pos[d] + br->tile->size[d]){
                //set direction of expansion
                if(dir_unset()){
                    dir = d;
                }
                //create a new brick in this Fold
                if(dir == d){
                    Brick* b = current_empty();
                    //drag from left (top), new brick on left (top)
                    if(pos[d] > pmouse_pos[d]){
                        b->tile->pos[d] = trigger_pos[d];
                        insert(b, drag-1);
                    }
                    //drag from right (bottom), new brick on right (bottom)
                    else{
                        b->tile->pos[d] = anchor_pos[d];
                        insert(b, drag);
                    }
                    created = true;
                }
                //create new Fold in opposite direction (if not already dragging)
                else if(!temp_brick){
                    if(Fold* f = dynamic_cast<Fold*>(bricks[drag-1])){
                        defer_fold(f);
                    }
                    else{
                        swap_live_fold(drag-1);
                    }
                }
            }
            //resize/remove bricks as necessary (re-check drag, it can be changed by fns above)
            if(created && dir == d && drag){
                bricks[drag-1]->tile->size[d] = pos[d] - bricks[drag-1]->tile->pos[d];
                bricks[drag]->tile->size[d] = anchor_pos[d] - pos[d];
                bricks[drag]->tile->pos[d] = pos[d];

                //min side remove brick
                if(pos[d] < trigger_pos[d] + trigger[d]){
                    bricks[drag]->tile->pos = bricks[drag-1]->tile->pos;
                    bricks[drag]->tile->size[d] += bricks[drag-1]->tile->size[d];
                    remove(drag-1);
                    created = false;
                }
                //max side remove brick
                if(pos[d] > anchor_pos[d] - trigger[d]){
                    bricks[drag-1]->tile->size[d] += bricks[drag]->tile->size[d];
                    remove(drag);
                    created = false;
                }
                bricks[drag-1]->update();
                bricks[drag]->update();
            }
        }
    }
    Brick::mouse(pos);
    pmouse_pos = pos;
}

void Fold::released(glm::vec2 pos, int button){
    if(drag){
        drag = 0;
        created = false;
        trash_empty(nullptr);
    }
    Brick::released(pos, button);
}

void Fold::update(){
    //make first brick full size
    if(dir == -1){
        Group* g = static_cast<Group*>(tile);
        g->in[0]->size = g->size;
        psize = tile->size;
    }
    //resize relative to previous size
    else if(psize != tile->size){
        //ratio of previus to current size
        double r = tile->size[dir]/psize[dir];
        Group* g = static_cast<Group*>(tile);
        //resize bricks along direction by ratio, against directly by size
        for(int i = 0; i<g->in.size()-1;i++){
            Tile* t = g->in[i];
            t->size[dir] *= r;
            t->size[!dir] = tile->size[!dir];
            g->in[i+1]->pos[dir] = t->pos[dir] + t->size[dir];
        }
        //resize last brick
        g->in[g->in.size()-1]->size[dir] = g->size[dir] - g->in[g->in.size()-1]->pos[dir];
        g->in[g->in.size()-1]->size[!dir] = tile->size[!dir];
        psize = tile->size;
    }
    Brick::update();
}

void Fold::remove(Brick* b){
    trash_empty(b);
    Brick::remove(b);
}
void Fold::remove(uint b){
    trash_empty(bricks[b]);
    Brick::remove(b);
}

//allocate new brick as necessary
Brick* Fold::current_empty(){
    if(temp_brick){
        Brick * t = temp_brick;
        temp_brick = nullptr;
        return t;
    }
    return new_empty();
}
//allocate new brick
Brick* Fold::new_empty(){
    Brick* b = new Brick();
    b->tile = new Tile();
    b->tile->size = tile->size;
    return b;
}
//remember or delete brick as necessary
void Fold::trash_empty(Brick* b){
    if(temp_brick) {
        delete_empty(temp_brick);
        temp_brick = b;
        return;
    }
    temp_brick = b;
}
//deallocate old brick
void Fold::delete_empty(Brick* b){
    if(b){
        delete b;
    }
}
//create new fold recursively
void Fold::swap_live_fold(uint i){
    Brick* b = bricks[i];
    Fold* f = new Fold(0);
    f->tile->pos = b->tile->pos;
    f->tile->size = b->tile->size;
    f->psize = f->tile->size;
    b->tile->pos = glm::vec2(0,0);
    replace(i, f);
    f->add(b);
    defer_fold(f);
}
//defer drag info to later fold
void Fold::defer_fold(Fold* f){
    f->trigger_pos = trigger_pos-f->tile->pos;
    f->anchor_pos = anchor_pos-f->tile->pos;
    f->drag = 1;
    f->created = false;
    f->dir = !dir;
    drag = 0;
}
bool Fold::dir_unset(){
    return dir == -1;
}

//a value representing what type of interaction would result from a click
int Fold::interact(const glm::vec2& pos){
    int a = check_interact(pos);
    if(a) return a;
    if(bricks.size() == 1){
        dir = -1;
    }
    Group* g = static_cast<Group*>(tile);
    for(int i=0;i<g->in.size();i++){
        Tile* t = g->in[i];
        int a[2] {0,0};
        int dout = -2;
        //check both directions
        for(int d=0;d<2;d++){
            //close edge
            if(pos[d] - trigger[d] < t->pos[d] && pos[d] >= t->pos[d] - 0.05){
                a[d] = 1;
            }
            //far edge
            else if(pos[d] + trigger[d] > t->pos[d] + t->size[d] && pos[d] <= t->pos[d] + t->size[d]){
                a[d] = 2;
            }
        }
        //corner
        if(a[0] && a[1]){
            return corner;
            break;
        }
        //edge
        else if (dout == dir){
            if( int b = a[0] | a[1] ){
                created = true;
                drag = 0;
                if(i < g->in.size()-1 && b == 2){
                    return edge;
                }
                if(i > 0 && b == 1){
                    return edge;
                }
                break;
            }
            //if(bricks[i]->tile->
        }
    }
    return none;
}