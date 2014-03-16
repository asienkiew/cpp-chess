/* 
 * File:   move.h
 * Author: sienio
 *
 * Created on 7 styczeń 2014, 00:33
 */

#ifndef MOVE_H
#define	MOVE_H
#include "figure.h"
#include <iostream>

class move {
public:
        char which_was_captured;
    unsigned char x1, x2, y1, y2;

    char promote_to;
    bool is_castling, is_enpassant, is_promotion, is_valid;
    
    figure::color c;
    char which_moved;

    move();
    move(std::string, figure::color);
    move(unsigned char,unsigned char,unsigned char,unsigned char, figure::color, char, char, char);
    bool is_opposite_to(move &);
    
    virtual ~move();
    friend std::ostream& operator<<(std::ostream&, move&);
    friend bool operator== (move &, move &);
private:
    

};

#endif	/* MOVE_H */

