/* 
 * File:   figure.cpp
 * Author: sienio
 * 
 * Created on 25 grudzień 2013, 15:09
 */

#include "figure.h"
#include <ctype.h>
figure::figure() {
  
}

figure::figure(color cc):c(cc) {
    jump_over = false;
    is_capturable = true;
}

figure::figure(const figure& orig) {
    sign = orig.sign;
    c = orig.c;
    jump_over = orig.jump_over;
}

figure::~figure() {
}
char figure::get_sign() {
    if (c == white) {
        return sign;    
    } else if (c == black){
        return tolower(sign);
    } else {
        return sign;
    }
    
};
char figure::get_sign_raw() {
 
        return sign;
   
    
};

void figure::set_possible_moves_table() {
    for (short int x1 = 0; x1 < 8; x1++) {  
        for (short int x2 = 0; x2 < 8; x2++) {
            for (short int y1 = 0; y1 < 8; y1++) {
                for (short int y2 = 0; y2 < 8; y2++) {
                    possible_normal_moves[x1][x2][y1][y2] = can_move(x1, x2, y1, y2);
                            
                }            
            }           
        }   
    }
}

bool figure::can_capture(short int x1, short int x2, short int y1, short int y2) {
    return this->can_move(x1, x2, y1, y2);
}
 bool figure::can_jump_over(){
     return jump_over;
 }
 figure::color figure::get_color(){
     return c;
 }  
 
 bool figure::can_be_captured(){
     return is_capturable;
 }