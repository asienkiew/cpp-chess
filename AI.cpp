/* 
 * File:   AI.cpp
 * Author: sienio
 * 
 * Created on 6 styczeń 2014, 16:59
 */

#include "AI.h"
#include "figure.h"


AI::AI(figure::color & c, checkboard * check):who(c), check(check) {
    opposite = c == figure::black ? figure::white : figure::black;
}


std::vector <move> AI::get_possible_moves(checkboard& check) {
     
     
    std::vector< move > possible_moves;
    possible_moves.clear();
    if (check.status != checkboard::in_progress) {
        possible_moves.clear();
    }
    std::vector < int_pair >::iterator it_pair;


    for (it_pair = check.figures_position[check.who_is_next].begin(); it_pair != check.figures_position[check.who_is_next].end(); ++it_pair) {       
        short int x1 = it_pair->first;
        short int y1 = it_pair->second;
  
        for (short int x2 = 0; x2 < 8; x2++) {
            for (short int y2 = 0; y2 < 8; y2++) {
                move m =  check.is_move_possible(x1, x2, y1, y2, check.who_is_next, 'H');

                if (m.is_valid ) {
                    possible_moves.push_back(m);
                  //  std::cout<<m<<"\n";
                }             
            }            
        }           
 
    } 
    
    return possible_moves;
 }