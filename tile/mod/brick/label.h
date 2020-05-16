#pragma once

#include "brick.h"
#include <string>

class Label : public Brick {
public:
    std::string text;
    Label(std::string text = "");
    virtual ~Label();
};