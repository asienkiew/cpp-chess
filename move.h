#ifndef MOVE_H
#define MOVE_H
#include "figure.h"
#include <iostream>

class move {
public:

    unsigned char x1, x2, y1, y2;
    bool is_castling, is_enpassant, is_promotion, is_valid;
    figure::color c;
    char which_moved, which_was_captured, promote_to;

    move();
    move(std::string, figure::color);
    move(unsigned char, unsigned char, unsigned char, unsigned char, figure::color, char, char, char);
    bool is_opposite_to(move &);
    std::string extended();
    std::string raw();

    virtual ~move();
    friend std::ostream& operator<<(std::ostream&, move&);
    friend bool operator==(move &, move &);
private:


};

#endif /* MOVE_H */

