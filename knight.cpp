/* 
 * File:   knight.cpp
 * Author: sienio
 * 
 * Created on 4 styczeń 2014, 20:45
 */

#include "knight.h"
#include <cmath>
#include <iostream>
knight::knight(figure::color cc):figure(cc){
    sign = 'S'; 
    jump_over = true;
    this->set_possible_moves_table();
    
}

knight::knight() {
}
knight::~knight() {
}

bool knight::can_move_raw(short int x1, short int x2, short int y1, short int y2) {
 
        if ( 
             (std::abs(x1 - x2) + std::abs(y1 - y2) == 3) && // może się przesunąc o 3 pola sumując x i y
                 ( std::abs(y1 - y2) != 0 && std::abs(x1 - x2) != 0)  // ale nie moż zostać w tej samej linii w pionie lub poziomie
           ) 
        {
            return true;   
        }

    return false;
}

