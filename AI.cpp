/* 
 * File:   AI.cpp
 * Author: sienio
 * 
 * Created on 6 styczeń 2014, 16:59
 */

#include "AI.h"
#include "figure.h"

AI::AI(figure::color c):who(c) {
}

AI::AI(const AI& orig) {
}

AI::~AI() {
}

int * AI::select_move(checkboard & check){
    
     for (int x1 = 7; x1 > -1; x1--) {
        
        for (int x2 = 0; x2 < 8; x2++) {
            for (int y1 = 0; y1 < 8; y1++) {
                for (int y2 = 0; y2 < 8; y2++) {
                    if (check.move_from_raw_coordinates(x1, x2, y1, y2, who) ) {
                           int t[4] ;
                            t[0] = x1;
                            t[1] = x2;
                            t[2] = y1;
                            t[3] = y2;
                            return t;
                        //return [x1, x2, y1, y2];
                        
                    }
              
                }
             
            }    
             
        }
        
    }
    
    
}