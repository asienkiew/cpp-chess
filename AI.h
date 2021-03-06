#ifndef AI_H
#define AI_H
#include "checkboard.h"
#include "figure.h"
#include <vector>
#include "move.h"
#include "player.h"

class AI : public player {
public:


    virtual move select_move() = 0;
    AI(figure::color, std::shared_ptr<checkboard>);

    std::vector <move> get_possible_moves(checkboard & check);
protected:
    typedef std::pair<unsigned char, unsigned char> int_pair;
};

#endif /* AI_H */

