/* 
 * File:   checkboard.cpp
 * Author: sienio
 * 
 * Created on 15 grudzień 2013, 22:34
 */
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <ctype.h>
#include "checkboard.h"
#include "figure.h"
#include "queen.h"
#include "bishop.h"
#include "rook.h"
#include "king.h"
#include "knight.h"
#include "empty.h"
#include "move.h"


//checkboard::checkboard(const checkboard& orig) {
//}

checkboard::checkboard() {
    is_castling_possible[figure::black] = true;    
    is_castling_possible[figure::white] = true;
    status = in_progress;
    who_is_next = figure::white;
    for (short int y=7; y>-1; y--) {

        for (short int x=0; x<8; x++) {
              empty * p      = new empty(figure::none); 
             //std::cout<<p->get_sign();
              board[x][y]= p;
             
        }
    }
    for (short int i=0; i<2; i++) {

        for (short int j=0; j<16; j++) {
             for (short int k=0; k<2; k++) {
                 figures_position[i][j][k] = -1;
             }  
        }
    } 
    king_pos[0][1] = & figures_position[0][15][1];
    king_pos[1][1] = & figures_position[1][15][1];
    king_pos[0][0] = & figures_position[0][15][0];
    king_pos[1][0] = & figures_position[1][15][0];

}

checkboard::~checkboard() {
       for (short int y=7; y>-1; y--) {
      
        for (short int x=0; x<8; x++) {
            delete board[x][y];
        }
    }
  
}

void checkboard::load_from_file(std::string& file) {
    
    std::ifstream  f(file.c_str());

    std::string linia; 
    short int non_king[2] = {0,0};
    
    for (short int y=7; y>-1; y--) {
        std::getline(f,linia);
        
        for (short int x=0; x<8; x++) {
            board[x][y] = sign_to_object(linia[x]);
            figure:: color  c = board[x][y]->get_color();
            
            //std::cout<<non_king[0]<< non_king[1]<<"\n" ;

            if (board[x][y]->get_color() != figure::none) {
                if ( non_king[0] > 15 || non_king[1] > 15)  {
                   throw "Bad data";
                   
                } 
                
                if (board[x][y]->get_sign_raw() == 'K') {
                    figures_position[c][15][0] = x;
                    figures_position[c][15][1] = y;
                } else {
                    figures_position[c][non_king[c]][0] = x;
                    figures_position[c][non_king[c]][1] = y;
                    
                     non_king[c]++;
                }
                
            }
 
        }
    }
  

  f.close();
}
void checkboard::save_to_file(std::string&) {
    
}

void checkboard::print() {
    
    //std::cout<<"*"<<check_whether_castling_is_possible(figure::black)<< "*\n";
    std::cout<<"\n"<<"   a b c d e f g h\n";

    for (short int y=7; y>-1; y--) {
        std::cout<<"\n"<<y+1<<"  ";
        for (short int x=0; x<8; x++) {
            if (board[x][y]->get_sign() == '.' ) {
                if ( (x + y) % 2 == 0) {
                    std::cout<<"\033[35;1m"<<board[x][y]->get_sign()<<"\033[0m ";
                } else {
                    std::cout<<"\033[37;1m"<<board[x][y]->get_sign()<<"\033[0m ";
                }
                
            } else {
                if (board[x][y]->get_color() == figure::black) {
                    std::cout<<"\033[31;1m"<<board[x][y]->get_sign()<<"\033[0m ";
                } else {
                    std::cout<<"\033[37;1m"<<board[x][y]->get_sign()<<"\033[0m ";
                }
                 
            }
           
             
        }
        std::cout<<" "<<y+1;
    }
    std::cout<<"\n\n"<<"   a b c d e f g h\n";
}



bool checkboard::is_another_figure_between(short int  x1, short int  x2, short int  y1, short int  y2) {
    if (x1 == x2){
       for (short int y = std::min(y1, y2) + 1; y < std::max(y1, y2); y++ ) {
           if (board[x1][y]->get_sign() != '.') {
               return true;
           }
       } 
    } else if (y1 == y2){
       for (short int x = std::min(x1, x2) + 1; x < std::max(x1, x2); x++ ) {
           if (board[x][y1]->get_sign() != '.') {
               return true;
           }
       }
    } else if (std::abs(x1 - x2) == std::abs(y1 - y2)) {
        short int sign_x = (x2 > x1) ? 1 : -1;
        short int sign_y = (y2 > y1) ? 1 : -1;
        for (short int i =  1; i < std::abs(x1 - x2); i++ ) {
            if (board[x1 + sign_x * i][y1 + sign_y * i]->get_sign() != '.') { 
                return true;
            } 
        }
    } else {
        return false;
    }
    return false;
}


short int * checkboard::to_table(std::string s){
   short int t[4] ;
   t[0] = int(s[0]) - 97;
   t[1] = int(s[1]) - 49;
   t[2] = int(s[2]) - 97;
   t[3] =  int(s[3]) - 49;
   return t;
}

bool checkboard::move_from_raw_coordinates(short int x1, short int x2, short int y1, short int y2, figure::color who_moves, char promote_to ) {
    
    move m = is_move_possible(x1,x2,y1,y2,who_moves, promote_to);
    if(m.is_valid) {
       return move_without_assert(m, true);        
    } else {
        return false;
    }
     
}

bool checkboard::move_from_string(std::string s, figure::color who_moves) {

    
    short int *table = to_table(s);
    short int x1 = table[0];
    short int x2 = table[2];
    short int y1 = table[1];
    short int y2 = table[3];   
     
    if (s.length() == 5) {
       return move_from_raw_coordinates(x1, x2, y1, y2, who_moves, toupper(s[4]));  
    } else {
       return move_from_raw_coordinates(x1, x2, y1, y2, who_moves);  
    }
   
} 


figure * checkboard::sign_to_object(char sign/*, figure::color c*/) {
    figure * f;
   switch(sign) {
        case 'k':
            f = new king(figure::black);
            break;
        case 'K':
            f = new  king(figure::white);
            break;
        case 'h':
            f = new  queen(figure::black);
            break;
        case 'H':
            f = new   queen(figure::white);
            break;
        case 'w':
            f = new   rook(figure::black);
            break;
        case 'W':
            f = new   rook(figure::white);          
            break;
        case 'p':
            f = new   pawn(figure::black);
            break;
        case 'P':
            f = new   pawn(figure::white);          
            break;
        case 's':
            f = new   knight(figure::black);
            break;
        case 'S':
            f = new   knight(figure::white);          
            break;
        case 'g':
            f = new   bishop(figure::black);
            break;
        case 'G':
            f = new   bishop(figure::white);          
            break;       
       case '*':
            f = new   empty(figure::none);          
            break;
        default:
            throw "BadSign";
            break;           
    } 
    
}
bool checkboard::move_without_assert(move m, bool add_to_history){
 
    short int pos1[2] = {m.x1, m.y1}; 
    short int pos2[2] = {m.x2, m.y2}; 

    if (board[m.x2][m.y2]->get_sign_raw() != '.') {
        figure::color opposite_player = board[m.x2][m.y2]->get_color();
        delete board[m.x2][m.y2];
        board[m.x2][m.y2] = board[m.x1][m.y1];
        
        board[m.x1][m.y1] = new empty(figure::none);
        
        update_figures_position(pos2, opposite_player, -1, -1) ;
  
        
        
    } else {
        figure * tmp = board[m.x2][m.y2];
        board[m.x2][m.y2] = board[m.x1][m.y1];
              
        board[m.x1][m.y1] = tmp;       
    }
    
    update_figures_position(pos1, m.c, m.x2, m.y2) ;
    
    //roszada
    if (m.is_castling) {
       short int rook_x1 = m.x2 > m.x1 ? 7 : 0; 
       short int rook_x2  = m.x2 > m.x1 ? 5 : 3;
       //y1 powinno być y2
       
       figure * tmp = board[rook_x2][m.y2];
       board[rook_x2][m.y2] = board[rook_x1][m.y1];
              
       board[rook_x1][m.y1] = tmp; 
       
       short int rook_pos[2] = {rook_x1, m.y1}; 
       update_figures_position(rook_pos, m.c, rook_x2, m.y2) ;
  
       
    }
    //en passant
    if (m.is_enpassant) {
        figure::color opposite_player = board[m.x2][m.y2]->get_color();
        delete board[m.x2][m.y1];
        board[m.x2][m.y1] = new empty(figure::none); 
        
            
         short int pawn_pos[2] = {m.x2, m.y1}; 
         update_figures_position(pawn_pos, opposite_player, -1, -1) ;
    }
    
    // promocja
    if (m.is_promotion) {
         char colored_promote_to; 
         if (m.c == figure::white) {
            colored_promote_to = m.promote_to;    
         } else if (m.c == figure::black){
            colored_promote_to = tolower(m.promote_to);  
         }
         
         delete board[m.x2][m.y2];
         board[m.x2][m.y2] = sign_to_object(colored_promote_to) ; 
     
     
    }
    
    if (add_to_history) {
        history.push_back(m) ;
        //std::cout<<is_in_check(m.c)<<"\n";
        std::cout<<m<<"\n";
        who_is_next = m.c == figure::black ? figure::white : figure::black;
        update_status();
    }

    return true;
}

bool checkboard::revert_move_without_assert(move m, bool remove_last_move_from_history){
    
    short int pos1[2] = {m.x1, m.y1}; 
    short int pos2[2] = {m.x2, m.y2}; 
    short int pos_null[2] = {-1,-1};
    
    figure::color opposite_player = m.c == figure::black ? figure::white : figure::black;
    char colored_sign;
    if (m.which_was_captured != '.') {
        
        if (opposite_player == figure::white) {
            colored_sign = m.which_was_captured;    
        } else if (opposite_player == figure::black){
            colored_sign = tolower(m.which_was_captured);  
        }
 
        
        delete board[m.x1][m.y1];
        board[m.x1][m.y1] = board[m.x2][m.y2];
       
        
        board[m.x2][m.y2] = sign_to_object(colored_sign) ;     
        update_figures_position(pos_null, opposite_player, m.x2, m.y2) ;

    } else {     
        figure * tmp = board[m.x2][m.y2];
        board[m.x2][m.y2] = board[m.x1][m.y1];
              
        board[m.x1][m.y1] = tmp;  
  
    }
     update_figures_position(pos2, m.c, m.x1, m.y1) ;
    //roszada
    if (m.is_castling) {
       short int rook_x1 = m.x2 > m.x1 ? 7 : 0; 
       short int rook_x2  = m.x2 > m.x1 ? 5 : 3;
  
       //swap
       figure * tmp = board[rook_x2][m.y2];
       board[rook_x2][m.y2] = board[rook_x1][m.y1];
              
       board[rook_x1][m.y1] = tmp; 
       
           
       short int rook_pos[2] = {rook_x2, m.y2}; 
       update_figures_position(rook_pos, m.c, rook_x1, m.y1) ;
    }
        //en passant
    char colored_pawn =  m.c == figure::white ? 'P' : 'p';
    char colored_opposite_pawn = m.c == figure::white ? 'p' : 'P'; 
    if (m.is_enpassant) {
         
        delete board[m.x2][m.y1];
        board[m.x2][m.y1] = sign_to_object(colored_opposite_pawn); 
        update_figures_position(pos_null, opposite_player, m.x2, m.y1) ;
        
    }
    //promocja
    if (m.is_promotion) {

         delete board[m.x1][m.y1];
         board[m.x1][m.y1] = sign_to_object(colored_pawn) ; 
     
    }

    if (remove_last_move_from_history) {
        history.pop_back() ;
        who_is_next = m.c;
        status = in_progress;
    }

    return true;
}
bool checkboard::check_whether_castling_is_possible(bool right_side, figure::color c){
    if (!is_castling_possible[c]) {
        return false;
    }
    std::vector < move >::iterator it = history.begin();
    short int rook_x = right_side ? 7 : 0;
    short int rook_y = c == figure::black ? 7 : 0;
    short int king_x = 4;
    
    
    for(; it != history.end(); it++ ){
        if ((it->c == c) && 
                ((it->which_moved == 'W' && it-> x1 == rook_x && it-> y1 == rook_y) 
               || it->which_moved == 'K')) {
            return false;
        }
    }
    //czy jest tam wieża
    if (board[rook_x][rook_y]->get_sign_raw() != 'W' || board[rook_x][rook_y]->get_color() != c) {
        return false;    
    }
    
    //czy nie ma nic pomiędzy   
    for (short int i = 1; i <  std::abs(king_x - rook_x); i++) { 
        short int x = king_x  - i + 2 * i * right_side;
        if ( board[x][rook_y]->get_sign_raw() != '.') {
            return false;            
        }
    }
    
    // pola gdzie: jest król, król przez nie przechodzi i będzie król nie są
    // szachowane
    figure::color opposite_color = c == figure::black ? figure::white : figure::black;

    for (short int i = 0; i <  3; i++) { 
        short int x = king_x  - i + 2 * i * right_side;
        if ( is_under_attack_by_any(x, rook_y, opposite_color)) {
            return false;            
        }
    }

    return true;    
}


move checkboard::is_move_possible(short int& x1, short int& x2,short int& y1,short int& y2, figure::color& who_moves, char promote_to) {
    
    
    char sign_from = board[x1][y1]->get_sign_raw();
    char sign_to = board[x2][y2]->get_sign_raw();
    move m(x1, x2, y1, y2, who_moves,sign_from, sign_to, promote_to);
    
    if (who_moves != who_is_next) {
        m.is_valid = false;
        return m;
    }

    
    // to też sprawdza czy na tym polu jest jakakolwiek figura
    if (who_moves != board[x1][y1]->get_color() ) {
        m.is_valid = false;
        return m;
    }
    
    //roszada          
    if (board[x1][y1]->get_sign_raw() == 'K' && std::abs(x1 -x2) == 2 && y1 == y2) {
          bool right_side  = x2 - x1 > 0;
          if (check_whether_castling_is_possible(right_side, who_moves)) {
              m.is_castling = true;
           
          } else {
            m.is_castling = true;
            m.is_valid = false;
          }
          return m;
    }
    // enpassant
    if (history.size() > 0) {
        move last_move = history.back();
    
        if ((board[x2][y2]->get_sign_raw() == '.') &&  
            (std::abs(x1 - x2) == 1) && 
                   (board[x1][y1]->get_sign_raw() == 'P') && 
                        last_move.x1 == x2 && 
                            last_move.x2 == x2 && 
                               last_move.y2 == y1 && 
                                   last_move.y1 == y1 + 2 * (y2- y1) &&
                                        last_move.which_moved == 'P') {
           if (!will_be_in_check(m)) {
               m.is_enpassant = true;
               return m;
           }
  
        }
    }       
    
    //zbijanie swojego    
    if (who_moves == board[x2][y2]->get_color() ) {
         m.is_valid = false;
        return m;
    }    
    
    //przeskakiwanie
    if (!board[x1][y1]->can_jump_over()) {
        if (is_another_figure_between(x1,x2,y1,y2)) {
            m.is_valid = false;
            return m;
        }   
    }
    
    
    //typowy ruch
    if ((sign_to == '.' &&  board[x1][y1]->can_move(x1,x2,y1,y2) ) || 
         ((sign_to != '.' && 
               board[x1][y1]->can_capture(x1,x2,y1,y2) && 
                   board[x2][y2]->can_be_captured()))) {  
       if (!will_be_in_check(m)) {
           if (sign_from == 'P' && (y2 == 7 || y2 == 0)) {
               m.is_promotion = true;
           }
           return m;   
       }
    } 
   
     m.is_valid = false;
     return m;
}

void checkboard::update_status() {
    bool is_any_move_possible_var = is_any_move_possible(who_is_next);
    bool is_in_check_var = is_in_check(who_is_next);
    if (!is_any_move_possible_var) {
        if (is_in_check_var) {
            if (who_is_next == figure::black) {
                status = white_won;
            } else {
                status = black_won;
            }
        } else {
            status = draw;
        }
    }
    
}

bool checkboard::is_stalemate(figure::color who_moves) {
    if (!is_any_move_possible(who_moves) && !is_in_check(who_moves)) {
        return true;
    }
}
bool checkboard::is_checkmate(figure::color who_moves){
    if (!is_any_move_possible(who_moves) && is_in_check(who_moves)) {
        return true;
    }
}

bool checkboard::is_any_move_possible(figure::color& who_moves){
    
    for (short int i = 0; i < 16; i++) {       
        short int x1 = figures_position[who_moves][i][0];
        short int y1 = figures_position[who_moves][i][1];
        if (x1 > -1 && y1 > -1) {
            for (short int x2 = 0; x2 < 8; x2++) {
                for (short int y2 = 0; y2 < 8; y2++) {
                    if (is_move_possible(x1,x2,y1,y2,who_moves, 'H').is_valid ) {
                            return true;
                    }             
                }
            }   
        }
  
       
    } 
    return false;
}

bool checkboard::is_in_check(figure::color& who_moves){
   
    figure::color who_is_trying_to_check = who_moves == figure::black ? figure::white : figure::black;
     
    return is_under_attack_by_any(*king_pos[who_moves][0], *king_pos[who_moves][1],  who_is_trying_to_check);

}

bool checkboard::is_under_attack_by_any(short int & x, short int & y, figure::color& who_is_trying_to_attack){
    
    for (short int i = 0; i < 16; i++) {       
        short int x1 = figures_position[who_is_trying_to_attack][i][0];
        short int y1 = figures_position[who_is_trying_to_attack][i][1];
        if (x1 > -1 && y1 > -1) {
            if (is_under_attack_by_given(x1, x, y1, y, who_is_trying_to_attack)) {
                return true;
            }            
        }    
     }
     return false;
}

bool checkboard::is_under_attack_by_given(short int& x1, short int& x2,short int& y1,short int& y2, figure::color& who_moves) {
    
    if (who_moves != board[x1][y1]->get_color() ) {
        return false;
    }
    
    if (!board[x1][y1]->can_jump_over()) {
        if (is_another_figure_between(x1,x2,y1,y2)) {
            return false;
        }   
    }
    if  (board[x1][y1]->can_capture(x1,x2,y1,y2)) {
        return true;
    }
    return false;
}

bool checkboard::will_be_in_check(move m, bool opposite_player) {
    bool will_be ;
    
    move_without_assert(m, false);
    figure::color c = m.c;
    if (opposite_player) {
         c = m.c == figure::black ? figure::white : figure::black;
    }
    
    will_be = is_in_check(c);
    revert_move_without_assert(m, false);
    return will_be;
}

void checkboard::update_figures_position(short int coordinates[], figure::color c, short int  x, short int  y) {
    
        for (short int i = 0; i<16; i++) {
            if (figures_position[c][i][0] == coordinates[0] && 
                    figures_position[c][i][1] == coordinates[1]  ) {
               figures_position[c][i][0] = x;
               figures_position[c][i][1] = y;
               return;
            }
           
        }
   
  
}