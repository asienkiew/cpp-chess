/* 
 * File:   king.h
 * Author: sienio
 *
 * Created on 4 styczeń 2014, 20:56
 */

#ifndef KING_H
#define	KING_H
#include "figure.h"

class king : public figure{
public:
    
    static const bool can_jump_over = true;
    king(figure::color cc);
    virtual bool can_move(int x1, int x2, int y1, int y2);
    
private:

};

#endif	/* KING_H */

