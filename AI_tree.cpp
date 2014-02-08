/* 
 * File:   AI_tree.cpp
 * Author: sienio
 * 
 * Created on 5 luty 2014, 21:39
 */

#include "AI_tree.h"
#include "AI.h"
#include "checkboard.h"
#include "figure.h"
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>


AI_tree::AI_tree(figure::color c):AI(c) {
   opposite = c == figure::black ? figure::white : figure::black;
  // std::cout<< AI_tree::H_TABLE_WHITE[2][1];
}

AI_tree::~AI_tree() {
}

void AI_tree::select_move(checkboard& check) {
    
 
    std::map<int, move> possible_moves;
    std::vector < move >::iterator it;
     std::clock_t t1 = std::clock();
    for (short int i = 0; i < 16; i++) {       
        short int x1 = check.figures_position[who][i][0];
        short int y1 = check.figures_position[who][i][1];
        if (x1 > -1 && y1 > -1) {
            for (short int x2 = 0; x2 < 8; x2++) {
                for (short int y2 = 0; y2 < 8; y2++) {
                    
                    move m = check.is_move_possible(x1, x2, y1, y2, who, 'H');
                    if (m.is_valid ) {
                        //short int * a[16][2] = check.figures_position;
                        check.move_without_assert(m, true);
                        int s = get_score(check);
                        std::cout<<s<<"\n";
                        check.revert_move_without_assert(m, true);
                       // check.print();
                        possible_moves[s] = m;
                    }             
                }            
            }           
        }   
    }
     int max = -10000;
    for(std::map<int,move>::iterator it = possible_moves.begin(); it != possible_moves.end(); ++it) {
      if ( it->first > max) {
          max = it->first;
      }
      
    }
     check.move_without_assert(possible_moves[max], true);
    
}
int AI_tree::evaluation_function(checkboard & check, figure::color player) {
    
    int score = 0;
    for (short int i = 0; i< 16; i++) {
        short int x = check.figures_position[player][i][0];
        short int y = check.figures_position[player][i][1];
        if (x < 0 || y < 0) {
            continue;
        }
        char sign = check.board[x][y]->get_sign_raw();
  
        switch(sign) {
            case 'H':
                score += H_VALUE;
                if (player == figure::white) {
                    score += H_TABLE_WHITE[x][y];
                } else {
                    score += H_TABLE_BLACK[x][y]; 
                }
                break;
            case 'W':
                score += W_VALUE;
                if (player == figure::white) {
                    score += W_TABLE_WHITE[x][y];
                } else {
                    score += W_TABLE_BLACK[x][y]; 
                }
                break;
            case 'G':
                score += G_VALUE;
                if (player == figure::white) {
                    score += G_TABLE_WHITE[x][y];
                } else {
                    score += G_TABLE_BLACK[x][y]; 
                }
                break;
            case 'S':
                score += S_VALUE;
                if (player == figure::white) {
                    score += S_TABLE_WHITE[x][y];
                } else {
                    score += S_TABLE_BLACK[x][y]; 
                }
                break;
            case 'P':
                score += P_VALUE;
                if (player == figure::white) {
                    score += P_TABLE_WHITE[x][y];
                } else {
                    score += P_TABLE_BLACK[x][y]; 
                }
                break; 
        }
    }
    
    return score;
    
   
}

int AI_tree::get_score(checkboard & check) {
    checkboard::STATUS status = check.status;
    switch(status) {
        case checkboard::black_won:
            if (who == figure::black) {
                return WIN;
            } else {
                return -WIN;
            }
              
        case checkboard::white_won:
             if (who == figure::black) {
                return -WIN;
            } else {
                return WIN;
            }
       case checkboard::draw:
           return DRAW;
       default:
           break; 
    }
    return evaluation_function(check, who) - evaluation_function(check,opposite);
}