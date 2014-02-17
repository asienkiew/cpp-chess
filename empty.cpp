/* 
 * File:   empty.cpp
 * Author: sienio
 * 
 * Created on 4 styczeń 2014, 21:00
 */

#include "empty.h"
#include <cmath>
empty::empty(figure::color cc):figure(cc){
    sign = '.';
    this->set_possible_moves_table();
}
empty::empty() {
}

empty::~empty() {
}

bool empty::can_move_raw(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2) {
    return false;
}