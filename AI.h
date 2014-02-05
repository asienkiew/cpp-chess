/* 
 * File:   AI.h
 * Author: sienio
 *
 * Created on 6 styczeń 2014, 16:59
 */

#ifndef AI_H
#define	AI_H
#include "checkboard.h"
#include "figure.h"

class AI {
public:
    figure::color who;
    void select_move(checkboard & check);
    AI(figure::color c);
    AI(const AI& orig);
    virtual ~AI();
private:
 
};

#endif	/* AI_H */

