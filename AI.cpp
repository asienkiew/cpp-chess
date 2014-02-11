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

move AI::select_move(){      
}

std::vector <move> AI::get_possible_moves(checkboard& check) {
     
     
    std::vector< move > possible_moves;
   
    if (check.status != checkboard::in_progress) {
        possible_moves.clear();
    }
    for (short int i = 0; i < 16; i++) {       
        short int x1 = check.figures_position[check.who_is_next][i][0];
        short int y1 = check.figures_position[check.who_is_next][i][1];
        
        //std::cout<<check.figures_position[check.who_is_next][i][0]<<"*"<<check.figures_position[check.who_is_next][i][1];
                if (x1 > -1 && y1 > -1) {
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
    } 
    
    return possible_moves;
 }