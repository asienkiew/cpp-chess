/*
 * File:   pawn.h
 * Author: sienio
 *
 * Created on 25 grudzień 2013, 15:36
 */

#ifndef PAWN_H
#define	PAWN_H
#include "figure.h"

class pawn : public figure {
public:

    pawn(figure::color cc);
    pawn();
    virtual ~pawn();
    bool can_move_raw(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2);
    bool can_capture_raw(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2);

private:

};

#endif	/* PAWN_H */

