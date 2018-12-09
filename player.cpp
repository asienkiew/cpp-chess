#include "player.h"

player::player(figure::color c, std::shared_ptr<checkboard> check) : who(c), check(check) {
    opposite = c == figure::black ? figure::white : figure::black;
    std::cout << "player\n";
}

std::string player::get_type() {
    return this->type;
}