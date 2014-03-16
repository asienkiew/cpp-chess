/* 
 * File:   player.h
 * Author: sienio
 *
 * Created on 17 luty 2014, 00:52
 */

#ifndef PLAYER_H
#define	PLAYER_H
#include "figure.h"
#include "checkboard.h"

class player {
public: 
    virtual ~player();
    virtual move select_move() = 0;
    
protected:
    player(figure::color , checkboard * check);
    figure::color who, opposite;
    checkboard * check;
    player();
    player(const player& orig);

private:

};

#endif	/* PLAYER_H */

