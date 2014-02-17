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
    
    static const bool can_jump_over = false;
    king(figure::color cc);
    virtual bool can_move_raw(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2);
    virtual bool can_capture_raw(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2);
    king();
private:

};

#endif	/* KING_H */

