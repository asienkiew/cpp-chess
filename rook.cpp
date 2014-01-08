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

bool rook::can_move(short int x1, short int x2, short int y1, short int y2) {
 
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
