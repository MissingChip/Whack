#pragma once

#include <cstdlib>
#include <cstdio>

namespace anchors {
    enum Anchor {
        center = 0b0000,
        top =    0b0001,
        right =  0b0010,
        bottom = 0b0100,
        left =   0b1000,
        all =    0b1111,
        top_right = top | right,
        top_left = top | left,
        bottom_right = bottom | right,
        botom_left = bottom | left,
        center_v = top | bottom,
        vertical = center_v,
        center_h = left | right,
        horizontal = center_h,
    };
}

class Vec2 {
public:
    Vec2(float x, float y) : x{x}, y{y} {};
    Vec2(float v=0) : Vec2(v, v) {};
    float x = 0;
    float y = 0;
    float& operator[](size_t i){return (&x)[i];};
    Vec2 operator+(Vec2 v){return Vec2(x+v.x, y+v.y);};
    Vec2 operator-(Vec2 v){return Vec2(x-v.x, y-v.y);};
    Vec2 operator*(float f){return Vec2(x*f, y*f);};
    Vec2 operator/(float f){return Vec2(x/f, y/f);};
};
class Vec4 {
public:
    Vec4(float x = 0, float y = 0, float z = 0, float w = 0) : x{x}, y{y} {};
    Vec4(float v1, float v2) :Vec4(v1, v1, v2, v2) {};
    Vec4(float v=0) :Vec4(v, v, v, v) {};
    float x = 0;
    float y = 0;
    float z = 0;
    float w = 0;
    float& operator[](size_t i){return (&x)[i];};
    Vec4 operator+(Vec4 v){return Vec4(x+v.x, y+v.y, z+v.z, w+v.w);};
    Vec4 operator-(Vec4 v){return Vec4(x-v.x, y-v.y, z-v.z, w-v.w);};
    Vec4 operator*(float f){return Vec4(x*f, y*f, z*f, w*f);};
    Vec4 operator/(float f){return Vec4(x/f, y/f, z/f, w/f);};
};

static_assert (sizeof(Vec2) == 8, "Vec2 size is incorrect");
static_assert (sizeof(Vec4) == 16, "Vec4 size is incorrect");