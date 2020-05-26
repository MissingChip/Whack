#pragma once

#include "modifier.h"

class SplitMod : public Modifier{
public:
    SplitMod(bool direction=0, bool ratio=true, float start = 0.5);
    virtual ~SplitMod();
    bool dir = 0;
    bool ratio;
    float split;
    virtual void apply(Group*);
private: /* helpers */
};