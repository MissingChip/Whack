
#include "rowbox.h"

#include <math.h>

using namespace std;

void RowBox::update()
{
    if(children.size() > 0){
        if(attach == TOP)
            grow_down(); return;
        if(attach == BOTTOM)
            grow_up(); return;
        if(attach == RIGHT)
            grow_left(); return;
        if(attach == LEFT)
            grow_right(); return;
    }
}
void RowBox::set_margins(const Rose& margins)
{
    this->margins = margins;
}
void RowBox::set_spacing(const Pos& space)
{
    if(space.x>=0){spacing.x = space.x;}
    if(space.y>=0){spacing.y = space.y;}
}
void RowBox::set_spacing(double first, double last)
{
    if(first >= 0){spacing.x = first;}
    if(last >= 0){spacing.y = last;}
}
void RowBox::set_spacing(double amt)
{
    if(amt >= 0){
        spacing.x = amt/2;
        spacing.y = amt/2;
    }
}
void RowBox::attach_to(AnchorLoc side)
{
    if(is_side(side)){
        this->attach = side;
    }else{
        fprintf(stderr, "Not a side, using TOP\n");
        this->attach = TOP;
    }
}
AnchorLoc RowBox::get_attach()
{
    return attach;
}
void RowBox::grow_from(AnchorLoc side)
{
    attach_to(side);
}

void RowBox::grow_down()
{
    double space = box.h - (spacing.top+spacing.bottom)*children.size();
    double flex = 0;
    double at = box.h - margins.top;
    Pos force;
    force.h = (spacing.top+spacing.bottom)*children.size();

    for(int i=0;i<children.size();i++){
        space -= children[i]->full_min_h();
        flex += children[i]->flex.y;
    }
    if(flex == 0) flex = 1.0;
    space = max(space, 0.0);
    for(int i=0;i<children.size();i++){
        Tile* child = children[i];
        force.w = max(force.w, child->full_min_w());
        child->set_h(child->full_min_h() + child->flex.y/flex*space);
        at -= (spacing.top + child->padding.top + child->full_min_h());
        child->set_y(at);
        at -= (spacing.bottom+child->padding.bottom);
        stick_tile(child);
    }
    child_size = force;
}
void RowBox::grow_up()
{
    double space = box.h - (spacing.top+spacing.bottom)*children.size();
    double flex = 0;
    double at = 0;
    Pos force;
    force.h = (spacing.top+spacing.bottom)*children.size();

    for(int i=0;i<children.size();i++){
        space -= children[i]->full_min_h();
        flex += children[i]->flex.y;
    }
    if(flex == 0) flex = 1.0;
    space = max(space, 0.0);
    for(int i=0;i<children.size();i++){
        Tile* child = children[i];
        force.w = max(force.w, child->full_min_w());
        child->set_h(child->full_min_h() + child->flex.y/flex*space);
        at += spacing.bottom + child->padding.bottom;
        child->set_y(at);
        at += (child->full_min_h()+spacing.top+child->padding.top);
        stick_tile(child);
    }
    child_size = force;
}
void RowBox::grow_right()
{
    double space = box.w - (spacing.left+spacing.right)*children.size();
    double flex = 0;
    double at = 0;
    Pos force;
    force.w = (spacing.left+spacing.right)*children.size();

    for(int i=0;i<children.size();i++){
        space -= children[i]->full_min_w();
        flex += children[i]->flex.x;
    }
    if(flex == 0) flex = 1.0;
    space = max(space, 0.0);
    for(int i=0;i<children.size();i++){
        Tile* child = children[i];
        force.h = max(force.h, child->full_min_h());
        child->set_w(child->full_min_w() + child->flex.x/flex*space);
        at += spacing.left + child->padding.left;
        child->set_x(at);
        at += (child->box.w+spacing.right+child->padding.right);
        stick_tile(child);
    }
    child_size = force;
}
void RowBox::grow_left()
{
    double space = box.w - (spacing.left+spacing.right)*children.size();
    double flex = 0;
    double at = box.w - margins.x;
    Pos force;
    force.w = (spacing.left+spacing.right)*children.size();

    for(int i=0;i<children.size();i++){
        space -= children[i]->full_min_w();
        flex += children[i]->flex.x;
    }
    if(flex = 0){
        flex = 1;
    }
    space = max(space, 0.0);
    for(int i=0;i<children.size();i++){
        Tile* child = children[i];
        force.h = max(force.h, child->full_min_h());
        child->set_w(child->full_min_w() + child->flex.x/flex*space);
        at += spacing.left + child->padding.left + child->box.w;
        child->set_x(at);
        at += (spacing.right+child->padding.right);
        stick_tile(child);
    }
    child_size = force;
}

void RowBox::stick_tile(Tile* w)
{
    uint s = w->stick;
    if(s == none){
        s = default_stick();
    }
    if(attach == TOP || attach == BOTTOM){
        if((w->stick == TOP) || (w->stick == BOTTOM)){
            w->set_x((box.w-margins.right+margins.left-w->get_w())/2+w->padding.left);
        }
        if(w->stick & LEFT){
            w->set_x(margins.left + w->padding.left);
            w->set_w(w->get_min_w());
        }
        if(w->stick & RIGHT){
            if(!(w->stick & LEFT)) w->set_x(box.w-margins.right-w->get_w());
            w->set_w(box.w - w->box.x - w->padding.right - margins.right);
        }
    }
    if(attach == RIGHT || attach == LEFT){
        if((w->stick == RIGHT) || (w->stick == LEFT)){
            w->set_y((box.h-margins.top-margins.bottom-w->get_h())/2+margins.bottom+w->padding.bottom);
        }
        if(w->stick & BOTTOM){
            w->set_y(margins.bottom + w->padding.bottom);
            w->set_h(w->get_min_h());
        }
        if(w->stick & TOP){
            if(!(w->stick & BOTTOM)) w->set_y(box.h-margins.top-w->get_h());
            w->set_h(box.h - w->box.y - w->padding.top - margins.top);
        }
    }
}

AnchorLoc RowBox::default_stick()
{
    if(attach == TOP || attach == BOTTOM){
        return LEFT;
    }
    return TOP;
}