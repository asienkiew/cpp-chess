#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include "figure.h"
#include "checkboard.h"

class player {
public:
    virtual ~player() = default;
    virtual move select_move() = 0;
    virtual std::string get_type();

protected:
    std::string type;
    player(figure::color, std::shared_ptr<checkboard> check);
    figure::color who, opposite;
    std::shared_ptr<checkboard> check;

private:

};

#endif /* PLAYER_H */

