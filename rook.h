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
    virtual bool can_move(short int x1, short int x2, short int y1, short int y2);
    virtual ~rook();
private:

};

#endif	/* ROOK_H */

