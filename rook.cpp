/* 
 * File:   rook.cpp
 * Author: sienio
 * 
 * Created on 4 styczeń 2014, 20:20
 */

#include "rook.h"

#include <cmath>

rook::rook(figure::color cc):figure(cc){sign ='W';}


rook::~rook() {
}

bool rook::can_move(int x1, int x2, int y1, int y2) {
 
        if ( 
             (  
                (x1 == x2 && y1 != y2) || //ruch pionowo
                (y1 == y2 && x1 != x2) //ruch poziomo
             ) 
           ) 
        {
            return true;   
        }

    return false;
}
