
#pragma once

#include "container.h"

#include <string>

class Button : public Container
{
    Widget* in;
    Widget* child(int i);
};