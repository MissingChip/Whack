#pragma once

#include "group.h"
#include "tracker.h"

#include <string>
#include <unordered_map>

class WkRoot : Group {
    Tracker<Tile> track;
    std::unordered_map<std::string, uint> ids;
};