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
#include <vector>
#include "move.h"

class AI {
public:
    figure::color who, opposite;
    checkboard * check;
    move select_move();
    AI(figure::color &, checkboard *);

    std::vector <move> get_possible_moves(checkboard & check);
private:

};

#endif	/* AI_H */

