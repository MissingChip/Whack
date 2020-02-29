
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
    this->spacing = space;
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
void RowBox::grow_from(AnchorLoc side)
{
    attach_to(side);
}

void RowBox::grow_down()
{
    double space = box.h - spacing.top*children.size() - spacing.bottom*children.size();
    double flex = 0;
    double at = box.h - margins.top;

    for(int i=0;i<children.size();i++){
        space -= children[i]->full_min_h();
        flex += children[i]->flex.y;
    }
    if(flex == 0) flex = 1.0;
    space = max(space, 0.0);
    for(int i=0;i<children.size();i++){
        Widget* child = children[i];
        child->set_h(child->full_min_h() + child->flex.y/flex*space);
        at -= (spacing.top + child->padding.top + child->full_min_h());
        child->set_y(at);
        at -= (spacing.bottom+child->padding.bottom);
        stick_widget(child);
    }
}
void RowBox::grow_up()
{
    double space = box.h - spacing.top*children.size() - spacing.bottom*children.size();
    double flex = 0;
    double at = 0;

    for(int i=0;i<children.size();i++){
        space -= children[i]->full_min_h();
        flex += children[i]->flex.y;
    }
    if(flex == 0) flex = 1.0;
    space = max(space, 0.0);
    for(int i=0;i<children.size();i++){
        Widget* child = children[i];
        child->set_h(child->full_min_h() + child->flex.y/flex*space);
        at += spacing.bottom + child->padding.bottom;
        child->set_y(at);
        at += (child->full_min_h()+spacing.top+child->padding.top);
        stick_widget(child);
    }
}
void RowBox::grow_right()
{
    double space = box.w - spacing.left*children.size() - spacing.right*children.size();
    double flex = 0;
    double at = 0;

    for(int i=0;i<children.size();i++){
        space -= children[i]->full_min_w();
        flex += children[i]->flex.x;
    }
    if(flex == 0) flex = 1.0;
    space = max(space, 0.0);
    for(int i=0;i<children.size();i++){
        Widget* child = children[i];
        child->set_w(child->full_min_w() + child->flex.x/flex*space);
        at += spacing.left + child->padding.left;
        child->set_x(at);
        at += (child->box.w+spacing.right+child->padding.right);
        stick_widget(child);
    }
}
void RowBox::grow_left()
{
    double space = box.w - spacing.left*children.size() - spacing.right*children.size();
    double flex = 0;
    double at = box.w - margins.x;

    for(int i=0;i<children.size();i++){
        space -= children[i]->full_min_w();
        flex += children[i]->flex.x;
    }
    if(flex = 0){
        flex = 1;
    }
    space = max(space, 0.0);
    for(int i=0;i<children.size();i++){
        Widget* child = children[i];
        child->set_w(child->full_min_w() + child->flex.x/flex*space);
        at += spacing.left + child->padding.left + child->box.w;
        child->set_x(at);
        at += (spacing.right+child->padding.right);
        stick_widget(child);
    }
}

void RowBox::stick_widget(Widget* w)
{
    uint s = w->stick;
    if(s == none){
        s = default_stick();
    }
    if(attach == TOP || attach == BOTTOM){
        if(w->stick | LEFT){
            w->set_x(margins.left + w->padding.left);
            w->set_w(w->get_min_w());
        }
        if(w->stick | RIGHT){
            w->set_w(box.w - w->box.x - w->padding.right - margins.right);
        }
    }
    if(attach == RIGHT || attach == LEFT){
        if(w->stick | BOTTOM){
            w->set_y(margins.bottom + w->padding.bottom);
            w->set_h(w->get_min_h());
        }
        if(w->stick | TOP){
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