/* 
 * File:   queen.h
 * Author: sienio
 *
 * Created on 4 styczeń 2014, 17:20
 */

#ifndef QUEEN_H
#define	QUEEN_H
#include "figure.h"

class queen : public figure{
public:
   
    queen(figure::color cc);
    virtual bool can_move(int x1, int x2, int y1, int y2);
    virtual ~queen();
private:

};

#endif	/* QUEEN_H */

