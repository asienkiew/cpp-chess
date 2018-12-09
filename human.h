#ifndef HUMAN_H
#define HUMAN_H
#include "player.h"
#include "figure.h"

class human : public player {
public:
    human(figure::color c, std::shared_ptr<checkboard> check);

    virtual ~human() = default;
    move select_move();
    // sprawdza tylko czy format komendy jest poprawny
    bool is_command_ok(std::string s);

private:

};

#endif /* HUMAN_H */

