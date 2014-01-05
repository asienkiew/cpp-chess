/* 
 * File:   king.cpp
 * Author: sienio
 * 
 * Created on 4 styczeń 2014, 20:56
 */

#include "king.h"
#include <cmath>

king::king(figure::color cc):figure(cc){ sign = 'K';
  
}



bool king::can_move(int x1, int x2, int y1, int y2) {
 
        if  (std::abs(x1 - x2) == 1 || std::abs(y1 - y2) == 1) {
            return true;   
        }

    return false;
}

