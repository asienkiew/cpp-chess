/*
 * File:   queen.cpp
 * Author: sienio
 *
 * Created on 4 styczeń 2014, 17:20
 */

#include "queen.h"
#include <cmath>

queen::queen(figure::color cc):figure(cc){
    sign = 'H';
    this->set_possible_moves_table();
}

queen::queen() {
}
queen::~queen() {
}

bool queen::can_move_raw(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2 ) {

        if (
             (
                (x1 == x2 ) || //ruch pionowo
                (y1 == y2 ) || //ruch poziomo
                (std::abs(x1 - x2) == std::abs(y1 - y2)) // ruch po przekątnych
             ) && !(x1 == x2 && y1 == y2)  // nie może pozostać w miejscu
           )
        {
            return true;
        }

    return false;
}