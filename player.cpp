/* 
 * File:   player.cpp
 * Author: sienio
 * 
 * Created on 17 luty 2014, 00:52
 */

#include "player.h"

player::player(figure::color c, checkboard * check):who(c), check(check) {
     opposite = c == figure::black ? figure::white : figure::black;
     std::cout<<"player\n";
}

player::player(const player& orig) {
}

player::player() {
}

player::~player() {
}

std::string player::get_type(){
    return this->type;
}