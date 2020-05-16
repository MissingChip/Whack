
#include "label.h"

using namespace std;

Label::Label(string s): text{text} {
    tile = new Tile(0, 0, 100, 24);
}

Label::~Label(){
    delete tile;
}