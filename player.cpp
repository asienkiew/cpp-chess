/* 
 * File:   player.cpp
 * Author: sienio
 * 
 * Created on 17 luty 2014, 00:52
 */

#include "player.h"

player::player(figure::color c, checkboard * check):who(c), check(check) {
     opposite = c == figure::black ? figure::white : figure::black;
}


player::player(const player& orig) {
}

player::~player() {
    delete check;

}

