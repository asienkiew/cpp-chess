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
bool figure::can_move(short int x1, short int x2, short int y1, short int y2) {
    return true;
}
bool figure::can_capture(short int x1, short int x2, short int y1, short int y2) {
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