/* 
 * File:   queen.cpp
 * Author: sienio
 * 
 * Created on 4 styczeń 2014, 17:20
 */

#include "queen.h"
#include <cmath>

queen::queen(figure::color cc):figure(cc){sign = 'H';}


queen::~queen() {
}

bool queen::can_move(int x1, int x2, int y1, int y2 ) {
 
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