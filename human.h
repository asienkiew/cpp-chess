/*
 * File:   human.h
 * Author: sienio
 *
 * Created on 16 marzec 2014, 16:55
 */

#ifndef HUMAN_H
#define	HUMAN_H
#include "player.h"
#include "figure.h"

class human : public player{
public:
    human(figure::color c, checkboard * check);

    virtual ~human();
    move select_move();
    // sprawdza tylko czy format komendy jest poprawny
    bool is_command_ok(std::string s);

private:

};

#endif	/* HUMAN_H */

