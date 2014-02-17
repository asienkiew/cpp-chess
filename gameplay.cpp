/* 
 * File:   gameplay.cpp
 * Author: sienio
 * 
 * Created on 5 styczeń 2014, 18:48
 */

#include "gameplay.h"

gameplay::gameplay() {
}

gameplay::gameplay(const gameplay& orig) {
}

gameplay::~gameplay() {
}
void gameplay::start() {
    int counter = 1;
    while (check->status == check->in_progress) {
        this->players[counter % 2]->make_move(); 
        check->print();
        counter++;
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


