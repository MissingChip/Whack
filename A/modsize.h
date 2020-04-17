#pragma once

#include "modifier.h"

class MinSizeMod : public Modifier {
public:
    Vec2 size;
    virtual void apply(Group*);
};
class MaxSizeMod : public Modifier {
public:
    Vec2 size;
    virtual void apply(Group*);
};