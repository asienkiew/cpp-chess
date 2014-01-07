/* 
 * File:   figure.cpp
 * Author: sienio
 * 
 * Created on 25 grudzień 2013, 15:09
 */

#include "figure.h"
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
        return char(int(sign) + 32);
    } else {
        return sign;
    }
    
};
bool figure::can_move(int x1, int x2, int y1, int y2) {
    return true;
}
bool figure::can_capture(int x1, int x2, int y1, int y2) {
    return can_move(x1, x2, y1, y2);
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