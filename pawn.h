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
    bool can_move_raw(short int x1, short int x2, short int y1, short int y2);
    bool can_capture_raw(short int x1, short int x2, short int y1, short int y2);
    
private:
    
};

#endif	/* PAWN_H */

