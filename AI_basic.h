/* 
 * File:   AI_basic.h
 * Author: sienio
 *
 * Created on 31 styczeń 2014, 23:19
 */

#ifndef AI_BASIC_H
#define	AI_BASIC_H
#include "AI.h"
#include "checkboard.h"

class AI_basic : public AI {
public:    
    void select_move();
    AI_basic(figure::color c, checkboard *);
    
private:

};

#endif	/* AI_BASIC_H */

