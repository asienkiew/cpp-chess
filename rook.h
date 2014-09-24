/*
 * File:   rook.h
 * Author: sienio
 *
 * Created on 4 styczeń 2014, 20:20
 */

#ifndef ROOK_H
#define	ROOK_H
#include "figure.h"

class rook : public figure{
public:


    rook(figure::color cc);
    rook();
    virtual bool can_move_raw(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2);
    virtual ~rook();
private:

};

#endif	/* ROOK_H */

