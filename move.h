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
    unsigned char x1, x2, y1, y2;
    bool is_castling, is_enpassant, is_promotion, is_valid;
    char promote_to;
    figure::color c;
    char which_moved;
    char which_was_captured;
    move();
    move(unsigned char,unsigned char,unsigned char,unsigned char, figure::color, char, char, char);
    bool is_opposite_to(move &);
    
    virtual ~move();
    friend std::ostream& operator<<(std::ostream&, move&);
    friend bool operator== (move &, move &);
private:
    

};

#endif	/* MOVE_H */

