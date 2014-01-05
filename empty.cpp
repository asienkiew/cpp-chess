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

bool empty::can_move(int x1, int x2, int y1, int y2) {
    return false;
}