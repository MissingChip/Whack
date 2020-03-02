
#include "button.h"

Widget* Button::child(int i){
    return i == 0 ? in : nullptr;
}