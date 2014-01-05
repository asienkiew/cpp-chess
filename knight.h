/* 
 * File:   knight.h
 * Author: sienio
 *
 * Created on 4 styczeń 2014, 20:45
 */

#ifndef KNIGHT_H
#define	KNIGHT_H
#include "figure.h"

class knight : public figure {
public:
    
    static const bool can_jump_over = false;
    knight(figure::color cc);
    virtual bool can_move(int x1, int x2, int y1, int y2);
    virtual ~knight();
private:

};

#endif	/* KNIGHT_H */

