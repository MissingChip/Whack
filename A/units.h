
#pragma once

#include "widget.h"

class Unit
{
public:
    enum Type{
        px,
        percent,
        ratio,
        cm,
        mm,
        pt,
        pc,
        em,
        ch,
        rem,
        vw,
        vh,
        pw,
        ph,
        vmin,
        vmax
    } unit;
    
    double g();
    double get();
    double g(Type t);
    double get(Type t);
    double to(Type t);

private:
    Widget* parent;
    double val;
    template<class T>
    double operator=(T t);
};

template<class T>
double Unit::operator=(T t){
    return val = (double)t;
}