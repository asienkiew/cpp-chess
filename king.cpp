#include "king.h"
#include <cmath>

king::king(figure::color cc) : figure(cc) {
    sign = 'K';
    is_capturable = false;
    this->set_possible_moves_table();
}

bool king::can_move_raw(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2) {

    if (std::abs(x1 - x2) <= 1 && std::abs(y1 - y2) <= 1 && !(x1 == x2 && y1 == y2)) {
        return true;
    } else if (x1 == 4 && (x2 == 2 || x2 == 6) &&
            ((y1 == 0 && y2 == 0 && c == figure::white) ||
            (y1 == 7 && y2 == 7 && c == figure::black))) { //roszada
        return true;
    }

    return false;
}

bool king::can_capture_raw(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2) {
    if (std::abs(x1 - x2) <= 1 && std::abs(y1 - y2) <= 1 && !(x1 == x2 && y1 == y2)) {
        return true;
    }
    return false;
}