
#pragma once

#include "box.h"

#include <vector>

class SplitBox : public Box
{
public:
    virtual void update();
    virtual void click(double x, double y);
    virtual void hover(double x, double y);
    virtual void release(double x, double y);
    void orient(bool horizontal);
protected:
    std::vector<double> handles;
    double handle_width;
    double grabbed;
    int grabbed_handle;
    bool horizontal = true;
    Pos clicked;
private:
};