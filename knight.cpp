#include "knight.h"
#include <cmath>
#include <iostream>

knight::knight(figure::color cc) : figure(cc) {
    sign = 'S';
    jump_over = true;
    this->set_possible_moves_table();

}

bool knight::can_move_raw(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2) {

    if (
            (std::abs(x1 - x2) + std::abs(y1 - y2) == 3) && // może się przesunąc o 3 pola sumując x i y
            (std::abs(y1 - y2) != 0 && std::abs(x1 - x2) != 0) // ale nie moż zostać w tej samej linii w pionie lub poziomie
            ) {
        return true;
    }

    return false;
}

