
#pragma once

#include "box.h"

class GridBox : Box
{
    int rows;
    int cols;
    std::vector<double> row_min;
    std::vector<double> row_max;
    std::vector<double> col_min;
    std::vector<double> col_max;
};