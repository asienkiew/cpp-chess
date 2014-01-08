/* 
 * File:   empty.cpp
 * Author: sienio
 * 
 * Created on 4 styczeń 2014, 21:00
 */

#include "empty.h"
#include <cmath>
empty::empty(figure::color cc):figure(cc){sign = '.';}


empty::~empty() {
}

bool empty::can_move(short int x1, short int x2, short int y1, short int y2) {
    return false;
}