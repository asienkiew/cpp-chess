/* 
 * File:   AI.cpp
 * Author: sienio
 * 
 * Created on 6 styczeń 2014, 16:59
 */

#include "AI.h"
#include "figure.h"
#include <vector>
#include <cstdlib>

AI::AI(figure::color c):who(c) {
}

AI::AI(const AI& orig) {
}

AI::~AI() {
}

void AI::select_move(checkboard & check){
    srand (time(NULL));
    std::vector <move> possible_moves;

     for (short int x1 = 7; x1 > -1; x1--) {  
        for (short int x2 = 0; x2 < 8; x2++) {
            for (short int y1 = 0; y1 < 8; y1++) {
                for (short int y2 = 0; y2 < 8; y2++) {
                    move m = check.is_move_possible(x1, x2, y1, y2, who, 'H');
                    if (m.is_valid ) {
                        possible_moves.push_back(m);
                    }             
                }            
            }           
        }   
    }

   std::vector < move >::iterator it = possible_moves.begin();

   for(; it != possible_moves.end(); it++ ){
      std::cout<<*it<<"\n";
   } 
   check.move_without_assert(possible_moves[rand() % possible_moves.size()], true) ;
}