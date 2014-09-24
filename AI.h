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
#include "player.h"

class AI : public player {
public:


    virtual move select_move() = 0;
    AI(figure::color, checkboard *);

    std::vector <move> get_possible_moves(checkboard & check);
private:
   typedef std::pair<unsigned char, unsigned char> int_pair;
};

#endif	/* AI_H */

