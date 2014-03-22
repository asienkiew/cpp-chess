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
#include <boost/lexical_cast.hpp>
#include <algorithm> 




empty checkboard::EMPTY = empty(figure::none);
king checkboard::KING_B = king(figure::black);
king checkboard::KING_W = king(figure::white);
queen checkboard::QUEEN_B = queen(figure::black);
queen checkboard::QUEEN_W = queen(figure::white);
rook checkboard::ROOK_B =  rook(figure::black);
rook checkboard::ROOK_W = rook(figure::white);
pawn checkboard::PAWN_B = pawn(figure::black);
pawn checkboard::PAWN_W = pawn(figure::white);
knight checkboard::KNIGHT_B = knight(figure::black);
knight checkboard::KNIGHT_W = knight(figure::white);
bishop checkboard::BISHOP_B = bishop(figure::black);
bishop checkboard::BISHOP_W = bishop(figure::white);    

checkboard::checkboard() {
    srand (time(NULL));
    is_castling_possible[figure::black] = true;    
    is_castling_possible[figure::white] = true;
    status = in_progress;
    who_is_next = figure::white;



    for (unsigned char y=0; y<8; y++) {

        for (unsigned char x=0; x<8; x++) {
              board[x][y]= & EMPTY;
             
        }
    }

    figures_position.resize(2);
    figures_position[figure::black].resize(1);
    figures_position[figure::white].resize(1);
  

}

checkboard::~checkboard() {
       for (unsigned char y=0; y<8; y++) {
      
        for (unsigned char x=0; x<8; x++) {
           // delete board[x][y];
        }
    }
  
}
checkboard::checkboard(const checkboard& orig){
      who_is_next = orig.who_is_next;
    status = orig.status;
    history = orig.history;
    is_castling_possible[0] = orig.is_castling_possible[0];
    is_castling_possible[1] = orig.is_castling_possible[1];
    

    figures_position = orig.figures_position;

      
    for  (unsigned char y=0; y<8; y++) {
        for (unsigned char x=0; x<8; x++) {             
            board[x][y]= orig.board[x][y]; 
        }
    }


}
checkboard::checkboard(checkboard* orig) {
    who_is_next = orig->who_is_next;
    status = orig->status;
    history = orig->history;
    is_castling_possible[0] = orig->is_castling_possible[0];
    is_castling_possible[1] = orig->is_castling_possible[1];
    

    figures_position = orig->figures_position;

    
    for  (unsigned char y=0; y<8; y++) {
        for (unsigned char x=0; x<8; x++) {
            board[x][y]= orig->board[x][y]; 
        }
    }

    
   // return *this;
   // *this = orig;
      
}
checkboard& checkboard::operator= (const checkboard& orig ){
    who_is_next = orig.who_is_next;
    status = orig.status;
    history = orig.history;
    is_castling_possible[0] = orig.is_castling_possible[0];
    is_castling_possible[1] = orig.is_castling_possible[1];
    


    figures_position = orig.figures_position;

     
    for  (unsigned char y=0; y<8; y++) {
        for (unsigned char x=0; x<8; x++) {
             
           board[x][y]= orig.board[x][y]; 
        }
    }

    return *this;
    
}
void checkboard::load_from_file(std::string& file) {
    
    std::ifstream  f(file.c_str());

    std::string linia; 
    unsigned char non_king[2] = {0,0};
    int_pair coordinates;
    for (signed char y=7; y>=0; y--) {
        std::getline(f,linia);
        
        for (unsigned char x=0; x<8; x++) {
            coordinates = std::make_pair (x,y);
            //std::cout<<linia[x];
            board[x][y] = sign_to_object(linia[x]);
            figure:: color  c = board[x][y]->get_color();
            
            //std::cout<<non_king[0]<< non_king[1]<<"\n" ;

            if (board[x][y]->get_color() != figure::none) {
                if ( non_king[0] > 15 || non_king[1] > 15)  {
                   throw "Bad data";
                   
                } 
                
                if (board[x][y]->get_sign_raw() == 'K') {
                    figures_position[c][0] = coordinates;
                } else {
                    figures_position[c].push_back(coordinates);                    
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
    
    std::cout<<"\n"<<"   a b c d e f g h\n";

    for (signed char y=7; y>=0; y--) {
        std::cout<<"\n"<<y+1<<"  ";
        for (unsigned char x=0; x<8; x++) {
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



bool checkboard::is_another_figure_between(unsigned char  x1, unsigned char  x2, unsigned char  y1, unsigned char  y2) {
   // if (std::abs(y1 - y2) < 2 && std::abs(x1 - x2) < 2  ) {
  //      return false;
 //   }
    if (x1 == x2){
       for (unsigned char y = std::min(y1, y2) + 1; y < std::max(y1, y2); y++ ) {
           if (board[x1][y]->get_sign() != '.') {
               return true;
           }
       } 
    } else if (y1 == y2){
       for (unsigned char x = std::min(x1, x2) + 1; x < std::max(x1, x2); x++ ) {
           if (board[x][y1]->get_sign() != '.') {
               return true;
           }
       }
    } else if (std::abs(x1 - x2) == std::abs(y1 - y2)) {
        signed char sign_x = (x2 > x1) ? 1 : -1;
        signed char sign_y = (y2 > y1) ? 1 : -1;
        for (unsigned char i =  1; i < std::abs(x1 - x2); i++ ) {
            if (board[x1 + sign_x * i][y1 + sign_y * i]->get_sign() != '.') { 
                return true;
            } 
        }
    } else {
        return false;
    }
    return false;
}


bool checkboard::move_from_raw_coordinates(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2, figure::color who_moves, char promote_to ) {
    
    move m = is_move_possible(x1,x2,y1,y2,who_moves, promote_to);
    if(m.is_valid) {
       return move_without_assert(m, true);        
    } else {
        return false;
    }
     
}

bool checkboard::move_from_string(std::string s, figure::color who_moves) {

    
  
   unsigned char x1 = int(s[0]) - 97;
   unsigned char y1 = int(s[1]) - 49;
   unsigned char x2 = int(s[2]) - 97;
   unsigned char y2 = int(s[3]) - 49;
     
     
    if (s.length() == 5) {
       return move_from_raw_coordinates(x1, x2, y1, y2, who_moves, toupper(s[4]));  
    } else {
       return move_from_raw_coordinates(x1, x2, y1, y2, who_moves);  
    }
   
} 


figure * checkboard::sign_to_object(char sign) {
    figure * f;
   switch(sign) {
       case '.':
            f = & EMPTY;
            break;
        case 'k':
            f = &  KING_B;
            break;
        case 'K':
            f = &  KING_W;
            break;
        case 'h':
            f = & QUEEN_B;
            break;
        case 'H':
            f = & QUEEN_W;
            break;
        case 'w':
            f = &  ROOK_B  ;
            break;
        case 'W':
            f = & ROOK_W  ;          
            break;
        case 'p':
            f = & PAWN_B   ;
            break;
        case 'P':
            f = & PAWN_W  ;          
            break;
        case 's':
            f = & KNIGHT_B  ;
            break;
        case 'S':
            f = &  KNIGHT_W ;          
            break;
        case 'g':
            f = & BISHOP_B ;
            break;
        case 'G':
            f = & BISHOP_W;          
            break;       
       case '*':
            f = & EMPTY;         
            break;
        default:
            std::cerr<<"^"<<sign<<"^";
            throw "BadSign:";
            break;           
    } 
   return f;
    
}
bool checkboard::move_without_assert(move m, bool add_to_history){
 
    int_pair pos1 = std::make_pair(m.x1, m.y1); 
    int_pair pos2 = std::make_pair(m.x2, m.y2); 
    int_pair pos_null = std::make_pair(8,8);

    if (board[m.x2][m.y2]->get_sign_raw() != '.') {
        figure::color opposite_player = board[m.x2][m.y2]->get_color();

        board[m.x2][m.y2] = board[m.x1][m.y1];
        
        board[m.x1][m.y1] = & EMPTY;
        
        update_figures_position(pos2, opposite_player, pos_null) ;
  
        
        
    } else {

        std::swap (board[m.x2][m.y2], board[m.x1][m.y1]);
                 
    }
    
    update_figures_position(pos1, m.c, std::make_pair(m.x2, m.y2)) ;
    
    //roszada
    if (m.is_castling) {
       unsigned char rook_x1 = m.x2 > m.x1 ? 7 : 0; 
       unsigned char rook_x2  = m.x2 > m.x1 ? 5 : 3;
       //y1 powinno być y2
       
        std::swap (board[rook_x2][m.y2], board[rook_x1][m.y1]);

       int_pair rook_pos = std::make_pair(rook_x1, m.y1); 
       update_figures_position(rook_pos, m.c, std::make_pair(rook_x2, m.y2)) ;
       is_castling_possible[m.c] = false;
       
    }
    //en passant
    if (m.is_enpassant) {
        figure::color opposite_player = board[m.x2][m.y1]->get_color();

        board[m.x2][m.y1] = & EMPTY; 
        
            
         int_pair pawn_pos = std::make_pair(m.x2, m.y1); 
         update_figures_position(pawn_pos, opposite_player, pos_null) ;
    }
    
    // promocja
    if (m.is_promotion) {
         char colored_promote_to; 
         if (m.c == figure::white) {
            colored_promote_to = m.promote_to;    
         } else if (m.c == figure::black){
            colored_promote_to = tolower(m.promote_to);  
         } else {
             throw "m.c should be white or black";
         }
         

         board[m.x2][m.y2] = sign_to_object(colored_promote_to) ; 
     
     
    }
    
    if (add_to_history) {
        history.push_back(m) ;
        who_is_next = m.c == figure::black ? figure::white : figure::black;
        update_status();
    }

    return true;
}

bool checkboard::revert_move_without_assert(move m, bool remove_last_move_from_history){
    
    int_pair pos1 = std::make_pair(m.x1, m.y1); 
    int_pair pos2 = std::make_pair(m.x2, m.y2); 
    int_pair pos_null = std::make_pair(8,8);
    
    figure::color opposite_player = m.c == figure::black ? figure::white : figure::black;
    char colored_sign;
    if (m.which_was_captured != '.') {
        
        if (opposite_player == figure::white) {
            colored_sign = m.which_was_captured;    
        } else if (opposite_player == figure::black){
            colored_sign = tolower(m.which_was_captured);  
        }
 

        board[m.x1][m.y1] = board[m.x2][m.y2];
       
        
        board[m.x2][m.y2] = sign_to_object(colored_sign) ;     
        update_figures_position(pos_null, opposite_player, pos2) ;

    } else {     
        std::swap(board[m.x2][m.y2], board[m.x1][m.y1]);

  
    }
     update_figures_position(pos2, m.c, pos1) ;
    //roszada
    if (m.is_castling) {
       unsigned char rook_x1 = m.x2 > m.x1 ? 7 : 0; 
       unsigned char rook_x2  = m.x2 > m.x1 ? 5 : 3;

       std::swap(board[rook_x2][m.y2], board[rook_x1][m.y1]);

           
       int_pair rook_pos = std::make_pair(rook_x2, m.y2); 
       update_figures_position(rook_pos, m.c, std::make_pair(rook_x1, m.y1)) ;
       is_castling_possible[m.c] = true;
    }
        //en passant
    char colored_pawn =  m.c == figure::white ? 'P' : 'p';
    char colored_opposite_pawn = m.c == figure::white ? 'p' : 'P'; 
    if (m.is_enpassant) {
         
        board[m.x2][m.y1] = sign_to_object(colored_opposite_pawn); 
        update_figures_position(pos_null, opposite_player, std::make_pair(m.x2, m.y1)) ;
        
    }
    //promocja
    if (m.is_promotion) {

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
    unsigned char rook_x = right_side ? 7 : 0;
    unsigned char rook_y = c == figure::black ? 7 : 0;
    unsigned char king_x = 4;
    
    //czy jest tam wieża
    if (board[rook_x][rook_y]->get_sign_raw() != 'W' || board[rook_x][rook_y]->get_color() != c) {
        return false;    
    }
    
    for(; it != history.end(); it++ ){
        if ((it->c == c) && 
                ((it->which_moved == 'W' && it-> x1 == rook_x && it-> y1 == rook_y) 
               || it->which_moved == 'K')) {
            return false;
        }
    }

    
    //czy nie ma nic pomiędzy   
    for (unsigned char i = 1; i <  std::abs(king_x - rook_x); i++) { 
        unsigned char x = king_x  - i + 2 * i * right_side;
        if ( board[x][rook_y]->get_sign_raw() != '.') {
            return false;            
        }
    }
    
    // pola gdzie: jest król, król przez nie przechodzi i będzie król nie są
    // szachowane
    figure::color opposite_color = c == figure::black ? figure::white : figure::black;

    for (unsigned char i = 0; i <  3; i++) { 
        unsigned char x = king_x  - i + 2 * i * right_side;
        if ( is_under_attack_by_any(x, rook_y, opposite_color)) {
            return false;            
        }
    }

    return true;    
}


move checkboard::is_move_possible(unsigned char& x1, unsigned char& x2,unsigned char& y1,unsigned char& y2, figure::color& who_moves, char promote_to) {
    
    
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
    if (board[x1][y1]->get_sign_raw() == 'K' && std::abs(x1 -x2) == 2 && 
            board[x1][y1]->can_move(x1,x2,y1,y2)) {
          bool right_side  = x2 - x1 > 0;
          if (check_whether_castling_is_possible(right_side, who_moves)) {
              m.is_castling = true;
    
          } else {
            m.is_castling = false;
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
    // dwa króle
    } else if (figures_position[figure::black].size() == 1 && figures_position[figure::white].size() ==  1) {
        status = draw;
        return;
    } else {
        if (history.size() >= 12) {
            move last_move = history.back();
            move before_last_move = history[history.size()-2];
            //std::cout<<last_move<<"\n"<<before_last_move<<"\n";
            unsigned char last_moved_count = 0;
            unsigned char before_last_moved_count = 0;
            std::vector<move>::reverse_iterator rit;

            for (rit = history.rbegin(); rit!= history.rend(); ++rit) {
               
               if ( rit->which_was_captured != '.' ||
                       rit->which_moved == 'P' ||
                          rit->is_enpassant ||
                             rit->is_castling || 
                                rit->is_promotion) {
                   return;
               }
               if (*rit == last_move) {
                   last_moved_count++;
               }
               if (*rit == before_last_move) {
                   before_last_moved_count++;
               }
               if (before_last_moved_count >= 3 && last_moved_count >= 3) {
                   status = draw; 
                   return;
               }
            }

        }
    }



    
}

bool checkboard::is_stalemate(figure::color who_moves) {
    if (!is_any_move_possible(who_moves) && !is_in_check(who_moves)) {
        return true;
    }
    return false;
}
bool checkboard::is_checkmate(figure::color who_moves){
    if (!is_any_move_possible(who_moves) && is_in_check(who_moves)) {
        return true;
    }
    return false;
}

bool checkboard::is_any_move_possible(figure::color& who_moves){
    
    std::vector < int_pair >::iterator it_pair, it_pair2;
     
    for (it_pair = figures_position[who_moves].begin(); 
            it_pair != figures_position[who_moves].end(); ++it_pair) {       
        unsigned char x1 = it_pair->first;
        unsigned char y1 = it_pair->second;
        std::vector < int_pair > posible_move_for_figure = board[x1][y1]->get_possible_moves_for_figure(*it_pair);
        for (it_pair2 = posible_move_for_figure.begin(); it_pair2 != posible_move_for_figure.end(); ++it_pair2) {       
              
            if (is_move_possible(x1, it_pair2->first, y1, it_pair2->second,  who_moves, 'H').is_valid ) {
                        return true;
                }             
         
        }          
    } 
    return false;
}

bool checkboard::is_in_check(figure::color& who_moves){
   
    figure::color who_is_trying_to_check = who_moves == figure::black ? figure::white : figure::black;
     
    return is_under_attack_by_any(figures_position[who_moves][0].first, figures_position[who_moves][0].second,  who_is_trying_to_check);

}

bool checkboard::is_under_attack_by_any(unsigned char & x, unsigned char & y, figure::color& who_is_trying_to_attack){
    
    std::vector < int_pair >::iterator it_pair;
     
    for (it_pair = figures_position[who_is_trying_to_attack].begin(); 
            it_pair != figures_position[who_is_trying_to_attack].end(); ++it_pair) {       
        unsigned char x1 = it_pair->first;
        unsigned char y1 = it_pair->second;
        if (is_under_attack_by_given(x1, x, y1, y, who_is_trying_to_attack)) {
            return true;
        }            
    }    

    return false;
}

bool checkboard::is_under_attack_by_given(unsigned char& x1, unsigned char& x2,unsigned char& y1,unsigned char& y2, figure::color& who_moves) {
    
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

void checkboard::update_figures_position(int_pair & old_pos, figure::color c, int_pair new_pos) {
    
    std::vector < int_pair >::iterator it;
    if (old_pos.first == 8){
        figures_position[c].push_back(new_pos);
        return;
    } 
    for (it = figures_position[c].begin(); 
            it != figures_position[c].end(); ++it) {       

        if (*it == old_pos) {
            if (new_pos.first == 8) {
               figures_position[c].erase(it); 
            } else {
               *it = new_pos;
            }
            
            return;
        }
           
    }
  
}

std::string checkboard::serialize() {
    std::string s;
    
 
    
    for (unsigned char y=0; y<8; y++) {
  
        
        for (unsigned char x=0; x<8; x++) {
                  s += board[x][y]->get_sign();
         } 
    } 
    s+= boost::lexical_cast<std::string>(who_is_next);
    s+= boost::lexical_cast<std::string>(is_castling_possible[0]);
    s+= boost::lexical_cast<std::string>(is_castling_possible[1]);
    

    return s;
}