/* 
 * File:   bishop.cpp
 * Author: sienio
 * 
 * Created on 4 styczeń 2014, 20:41
 */

#include "bishop.h"

#include <cmath>

bishop::bishop(figure::color cc):figure(cc){
    sign = 'G';
    this->set_possible_moves_table();
}

bishop::bishop() {
}
bishop::~bishop() {
}

bool bishop::can_move_raw(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2) {
 
        if ( 
             (std::abs(x1 - x2) == std::abs(y1 - y2)) // ruch po przekątnych
             && !(x1 == x2 && y1 == y2) // nie może pozostać w miejscu  
           ) 
        {
            return true;   
        }

    return false;
}
