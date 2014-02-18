/* 
 * File:   player.h
 * Author: sienio
 *
 * Created on 17 luty 2014, 00:52
 */

#ifndef PLAYER_H
#define	PLAYER_H

class player {
public:
    player();
    player(const player& orig);
    virtual ~player();
    virtual void make_move() = 0;
private:

};

#endif	/* PLAYER_H */

