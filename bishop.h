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
    virtual bool can_move_raw(short int x1, short int x2, short int y1, short int y2);
    virtual ~bishop();
    bishop();
private:

};

#endif	/* BISHOP_H */

