/*
 * File:   bishop.h
 * Author: sienio
 *
 * Created on 4 styczeń 2014, 20:41
 */

#ifndef BISHOP_H
#define	BISHOP_H
#include "figure.h"

class bishop : public figure{
public:


    bishop(figure::color cc);
    virtual bool can_move_raw(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2);
    virtual ~bishop();
    bishop();
private:

};

#endif	/* BISHOP_H */

