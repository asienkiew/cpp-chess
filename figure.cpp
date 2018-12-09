#include "figure.h"
#include <ctype.h>
#include <iostream>
#include <vector>

figure::figure(color cc) : c(cc) {
    jump_over = false;
    is_capturable = true;

}

figure::figure(const figure& orig) {
    sign = orig.sign;
    c = orig.c;
    jump_over = orig.jump_over;
}

char figure::get_sign() {
    if (c == white) {
        return sign;
    } else if (c == black) {
        return tolower(sign);
    } else {
        return sign;
    }

};

char figure::get_sign_raw() {
    return sign;
};

void figure::set_possible_moves_table() {

    //std::cout<<"dups";
    possible_non_capture_moves.resize(8);
    possible_capture_moves.resize(8);
    all_moves.resize(8);

    for (unsigned char x1 = 0; x1 < 8; x1++) {
        possible_non_capture_moves[x1].resize(8);
        possible_capture_moves[x1].resize(8);
        all_moves[x1].resize(8);
        for (unsigned char y1 = 0; y1 < 8; y1++) {
            for (unsigned char x2 = 0; x2 < 8; x2++) {
                for (unsigned char y2 = 0; y2 < 8; y2++) {

                    int_pair to = std::make_pair(x2, y2);
                    std::vector<int_pair> empty_vector;
                    bool can_move_raw_var = this->can_move_raw(x1, x2, y1, y2);
                    bool can_capture_raw_var = this->can_capture_raw(x1, x2, y1, y2);

                    can_capture_bool_table[x1][y1][x2][y2] = can_capture_raw_var;
                    can_move_bool_table[x1][y1][x2][y2] = can_move_raw_var;

                    if (can_move_raw_var) {
                        possible_non_capture_moves[x1][y1].push_back(to);

                    }
                    if (can_capture_raw_var) {

                        possible_capture_moves[x1][y1].push_back(to);
                    }
                    if (can_capture_raw_var || can_move_raw_var) {

                        all_moves[x1][y1].push_back(to);
                    }
                }
            }
        }
    }
}

bool figure::can_capture_raw(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2) {
    return this->can_move_raw(x1, x2, y1, y2);
}

bool figure::can_capture(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2) {

    return can_capture_bool_table[x1][y1][x2][y2];
}

bool figure::can_move(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2) {

    return can_move_bool_table[x1][y1][x2][y2];
}

std::vector <figure::int_pair> & figure::get_possible_moves_for_figure(int_pair & p) {
    return this->all_moves[p.first][p.second];
}

bool figure::can_jump_over() {
    return jump_over;
}

figure::color figure::get_color() {
    return c;
}

bool figure::can_be_captured() {
    return is_capturable;
}