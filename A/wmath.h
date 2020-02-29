
#pragma once

#include <stdio.h>
#include <algorithm>
template<class T>
inline double wclamp(const T& a, const T& lo, const T& hi){
    return std::min(std::max(a, lo), hi);
}