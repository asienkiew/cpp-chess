#ifndef AI_BASIC_H
#define AI_BASIC_H
#include "AI.h"
#include "checkboard.h"

class AI_basic : private AI {
public:
    move select_move();
    AI_basic(figure::color c, std::shared_ptr<checkboard>);

private:

};

#endif /* AI_BASIC_H */

