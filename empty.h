/* 
 * File:   empty.h
 * Author: sienio
 *
 * Created on 4 styczeń 2014, 21:00
 */

#ifndef EMPTY_H
#define	EMPTY_H
#include "figure.h"

class empty : public figure{
public:
    
    empty(figure::color cc);
    bool can_move_raw(short int x1, short int x2, short int y1, short int y2);
    virtual ~empty();
    empty();
private:

};

#endif	/* EMPTY_H */

