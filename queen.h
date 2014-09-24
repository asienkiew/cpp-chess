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
    queen();
    virtual bool can_move_raw(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2);
    virtual ~queen();
private:

};

#endif	/* QUEEN_H */

