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
  
}

figure::figure(const figure& orig) {
    sign = orig.sign;
    c = orig.c;
  //  can_jump_over = orig.can_jump_over;
}

figure::~figure() {
}
char figure::get_sign() {
    return sign;
};
bool figure::can_move(int x1, int x2, int y1, int y2) {
    return true;
}
bool figure::can_capture(int x1, int x2, int y1, int y2) {
    return can_move(x1, x2, y1, y2);
}
  