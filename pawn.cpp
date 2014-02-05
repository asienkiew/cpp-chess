/* 
 * File:   pawn.cpp
 * Author: sienio
 * 
 * Created on 25 grudzień 2013, 15:36
 */
//#include "figure.h"
//#include "figure.cpp"
#include "pawn.h"
#include <cmath>




pawn::pawn(figure::color cc):figure(cc){
    sign = 'P';
    //set_possible_move_table();
}
pawn::~pawn() {
}



bool pawn::can_move(short int x1, short int x2, short int y1, short int y2 ) {
    if (c == figure::black) {
        if ((x1 == x2 && y1 == y2 + 1 ) || //ruch 1 do przodu
           (y1 == 6 && y2 == 4 && x1 == x2)) // ruch 2 do przodu w pozycji początkowej
        {
            return true;   
        }
    } else {
        if ((x1 == x2 && y2 == y1 + 1 ) || //ruch 1 do przodu
           (y1 == 1 && y2 == 3 && x1 == x2)) // ruch 2 do przodu w pozycji początkowej
        {
            return true;   
        } 
    }
    return false;
}

bool pawn::can_capture(short int x1, short int x2, short int y1, short int y2 ) {
    if (c == figure::black) {
        if (std::abs(x1 - x2) == 1 && y1 == y2 + 1) {
            return true;   
        }
    } else {
        if  (std::abs(x1 - x2) == 1 && y2 == y1 + 1 )  {
            return true;   
        } 
    }
    return false;
}  