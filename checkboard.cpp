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
         for (short int y=7; y>-1; y--) {

        for (short int x=0; x<8; x++) {
              empty * p      = new empty(figure::black); 
             //std::cout<<p->get_sign();
              board[x][y]= p;
             
        }
    }

}

checkboard::~checkboard() {
       for (short int y=7; y>-1; y--) {
      
        for (short int x=0; x<8; x++) {
            //delete board[x][y];
        }
    }
  
}

void checkboard::load_from_file(std::string& file) {
    
    std::ifstream  f(file.c_str());

    std::string linia; 
    
    for (short int y=7; y>-1; y--) {
        std::getline(f,linia);
        
        for (short int x=0; x<8; x++) {
            board[x][y] = sign_to_object(linia[x]);
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

std::string checkboard::to_string(short int* t){
    //return std::string(char(t[0] + 97)+char(t[1] + 49)+char(t[2] + 97)+char(t[3] + 49));
}

short int * checkboard::to_table(std::string s){
   short int t[4] ;
   t[0] = int(s[0]) - 97;
   t[1] = int(s[1]) - 49;
   t[2] = int(s[2]) - 97;
   t[3] =  int(s[3]) - 49;
   return t;
}

bool checkboard::move_from_raw_coordinates(short int x1, short int x2, short int y1, short int y2, figure::color who_moves) {
    char sign_from = board[x1][y1]->get_sign_raw();
    char sign_to = board[x2][y2]->get_sign_raw();
    move m(x1, x2, y1, y2, who_moves,sign_from, sign_to);
    
    if(is_move_possible(x1,x2,y1,y2,who_moves)) {
       return move_without_assert(m); 
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
     
    return move_from_raw_coordinates(x1, x2, y1, y2, who_moves);
}

void checkboard::push_move_to_history(short int x1, short int x2,short int y1,short int y2, figure::color c, char which_moved, char which_was_captured) {
    move m(x1, x2, y1, y2, c,which_moved, which_was_captured);
    history.push_back(m) ;
    

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
            //throw "sss";
           
    } 
    
}
bool checkboard::move_without_assert(move m){
    
    if (board[m.x2][m.y2]->get_sign_raw() != '.') {
        delete board[m.x2][m.y2];
        board[m.x2][m.y2] = board[m.x1][m.y1];
        
        board[m.x1][m.y1] = new empty(figure::none); 
        
    } else {
        figure * tmp = board[m.x2][m.y2];
        board[m.x2][m.y2] = board[m.x1][m.y1];
              
        board[m.x1][m.y1] = tmp;       
    }
    history.push_back(m) ;
    std::cout<<m<<"\n";
    return true;
}
bool checkboard::check_whether_castling_is_possible(figure::color c){
    std::vector < move >::iterator it = history.begin();
    for(; it != history.end(); it++ ){
        
        //TODO: błąd trzeba sprawdzać tylko jedną wieżę
        if ((it->c == c) && (it->which_moved == 'W' || it->which_moved == 'K')) {
            return false;
        }
    }
     return true;    
}
bool checkboard::is_move_possible(short int& x1, short int& x2,short int& y1,short int& y2, figure::color& who_moves) {

    if (who_moves != board[x1][y1]->get_color() ) {
        return false;
    }
    
    //zbijanie swojego    
    if (who_moves == board[x2][y2]->get_color() ) {
        return false;
    }    
    
    //przeskakiwanie
    if (!board[x1][y1]->can_jump_over()) {
        if (is_another_figure_between(x1,x2,y1,y2)) {
            return false;
        }   
    }
    
    //typowy ruch
    if (board[x1][y1]->get_sign() != '.') {
       if ((board[x2][y2]->get_sign() == '.' && board[x1][y1]->can_move(x1,x2,y1,y2))
               || ((board[x2][y2]->get_sign() != '.' && board[x1][y1]->can_capture(x1,x2,y1,y2) && board[x2][y2]->can_be_captured()))) {  
                     
           return true;
       } 
    }
    return false;
}


    bool checkboard::is_stalemate(figure::color& who_moves) {
        if (!is_any_move_possible(who_moves) && !is_check(who_moves)) {
            return true;
        }
    }
    bool checkboard::is_checkmate(figure::color& who_moves){
        if (!is_any_move_possible(who_moves) && is_check(who_moves)) {
            return true;
        }
    }
    bool checkboard::is_any_move_possible(figure::color& who_moves){
        
    }
    bool checkboard::is_check(figure::color& who_moves){
        
    }