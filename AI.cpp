/* 
 * File:   AI.cpp
 * Author: sienio
 * 
 * Created on 6 styczeń 2014, 16:59
 */

#include "AI.h"
#include "figure.h"
#include "player.h"


AI::AI(figure::color  c, checkboard * check):player(c, check) {

}


std::vector <move> AI::get_possible_moves(checkboard& check) {
     
     
    std::vector< move > possible_moves;
    possible_moves.clear();
    if (check.status != checkboard::in_progress) {
        possible_moves.clear();
        return possible_moves;
    }
    std::vector < int_pair >::iterator it_pair, it_pair2;

    
    for (it_pair = check.figures_position[check.who_is_next].begin(); it_pair != check.figures_position[check.who_is_next].end(); ++it_pair) {       
        unsigned char x1 = it_pair->first;
        unsigned char y1 = it_pair->second;
        std::vector < int_pair > posible_move_for_figure = check.board[x1][y1]->get_possible_moves_for_figure(*it_pair);
        for (it_pair2 = posible_move_for_figure.begin(); it_pair2 != posible_move_for_figure.end(); ++it_pair2) {       
            
            move m =  check.is_move_possible(x1, it_pair2->first, y1, it_pair2->second, check.who_is_next, 'H');
            
            if (m.is_valid ) {//std::cout<<m<<"\n";
               possible_moves.push_back(m);
              //  std::cout<<m<<"\n";
            }                     
        }           
 
    } 
    
    return possible_moves;
 }