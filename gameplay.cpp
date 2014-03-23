/* 
 * File:   gameplay.cpp
 * Author: sienio
 * 
 * Created on 5 styczeń 2014, 18:48
 */

#include "gameplay.h"
#include "human.h"
#include "AI_tree.h"

gameplay::gameplay(char * white_player_sign,  char * black_player_sign, std::string file) {
    check = new checkboard();
    check->load_from_file(file);
    check->print();
    
    if (*white_player_sign == 'H') {
        players[figure::white] = new human(figure::white, check);
    } else if  (*white_player_sign == 'C') {
        players[figure::white] = new AI_tree(figure::white, check, 4, 1);
    } else {
        throw "Sign should be H or C";
    }
    
    if (*black_player_sign == 'H') {
        players[figure::black] = new human(figure::black, check);
    } else if  (*black_player_sign == 'C') {
        players[figure::black] = new AI_tree(figure::black, check, 4, 2);
    } else {
        throw "Sign should be H or C";
    }
}

gameplay::gameplay(const gameplay& orig) {
}

gameplay::~gameplay() {
    delete players[0];
    delete players[1];
    delete check;
}
void gameplay::start() {
    while (check->status == check->in_progress) {
        move m = this->players[check->who_is_next]->select_move(); 
        check->move_without_assert(m, true);
        check->print();
    }
    if (check->status == check->black_won) {
         std::cout<<"\n***********************\n* Zwycięstwo czarnych *\n***********************\n"; 
    } else if (check->status == check->white_won) {
         std::cout<<"\n**********************\n* Zwycięstwo białych *\n**********************\n";  
    } else if (check->status == check->draw) {
         std::cout<<"\n**********************\n*******  Remis  ******\n**********************\n"; 
    } else {
         throw "Bad status";
    }
    
}


