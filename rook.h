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
    virtual bool can_move(int x1, int x2, int y1, int y2);
    virtual ~rook();
private:

};

#endif	/* ROOK_H */

