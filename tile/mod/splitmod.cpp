
#include <vector>

#include "splitmod.h"

using namespace std;
using namespace glm;

SplitMod::SplitMod(bool direction, bool ratio, float start) : dir{direction} , ratio{ratio}, split{start} {}
SplitMod::~SplitMod(){}

void SplitMod::apply(Group* g){
    vector<Tile*>& in = g->in;
    if(in.size() != 2) return;
    float pix_w = split;
    if(ratio){
        pix_w = g->size[dir]*split;
    }
    in[0]->pos = vec2(0,0);
    in[0]->size[dir] = pix_w;
    in[0]->size[!dir] = g->size[!dir];
    in[1]->pos[!dir] = 0;
    in[1]->pos[dir] = pix_w;
    in[1]->size[dir] = g->size[dir] - pix_w;
    in[1]->size[!dir] = g->size[!dir];
}