/* 
 * File:   king.cpp
 * Author: sienio
 * 
 * Created on 4 styczeń 2014, 20:56
 */

#include "king.h"
#include <cmath>

king::king(figure::color cc):figure(cc){ 
    sign = 'K';
    is_capturable = false;
  
}



bool king::can_move(short int x1, short int x2, short int y1, short int y2) {
 
        if  (std::abs(x1 - x2) <= 1 && std::abs(y1 - y2) <= 1 && !(x1 == x2 && y1 == y2)) {
            return true;   
        }

    return false;
}

