/* 
 * File:   gameplay.h
 * Author: sienio
 *
 * Created on 5 styczeń 2014, 18:48
 */

#ifndef GAMEPLAY_H
#define	GAMEPLAY_H
#include <string>
#include <vector>
#include "player.h"
#include "figure.h"
#include "checkboard.h"

class gameplay {
public:
    gameplay();
    gameplay(const gameplay& orig);
    virtual ~gameplay();
    void start();

private:
    checkboard * check;
    std::vector< std::string > history;
    player * players[2];
};

#endif	/* GAMEPLAY_H */

