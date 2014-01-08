/* 
 * File:   bishop.cpp
 * Author: sienio
 * 
 * Created on 4 styczeń 2014, 20:41
 */

#include "bishop.h"

#include <cmath>

bishop::bishop(figure::color cc):figure(cc){sign = 'G';}


bishop::~bishop() {
}

bool bishop::can_move(short int x1, short int x2, short int y1, short int y2) {
 
        if ( 
             (std::abs(x1 - x2) == std::abs(y1 - y2)) // ruch po przekątnych
             && !(x1 == x2 && y1 == y2) // nie może pozostać w miejscu  
           ) 
        {
            return true;   
        }

    return false;
}
