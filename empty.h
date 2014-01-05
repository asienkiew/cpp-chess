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
    bool can_move(int x1, int x2, int y1, int y2);
    virtual ~empty();
private:

};

#endif	/* EMPTY_H */

