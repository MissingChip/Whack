
#include <cstdio>

#include "vec.h"
int main(){
    int i = 2;
    int& i2 = i;
    printf("%d %d\n", i, i2);
    i2 = 3;
    printf("%d %d\n", i, i2);
    float a,b = 2;
    printf("%f %f\n", a, b);
}