#pragma once

#include "coat.h"
#include <string>

class Label : public Coat {
public:
    std::string text;
    Label(std::string text = "");
    virtual ~Label();
};