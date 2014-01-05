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
    virtual bool can_move(int x1, int x2, int y1, int y2);
    virtual ~bishop();
private:

};

#endif	/* BISHOP_H */

