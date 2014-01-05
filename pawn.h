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

    virtual ~pawn();
    bool can_move(int x1, int x2, int y1, int y2);
    bool can_capture(int x1, int x2, int y1, int y2);
private:
    
};

#endif	/* PAWN_H */

