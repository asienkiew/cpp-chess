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


//checkboard::checkboard(const checkboard& orig) {
//}

checkboard::checkboard() {
         for (int y=7; y>-1; y--) {

        for (int x=0; x<8; x++) {
              empty * p      = new empty(figure::black); 
             //std::cout<<p->get_sign();
              board[x][y]= p;
             
        }
    }

}

checkboard::~checkboard() {
   
}

void checkboard::load_from_file(std::string& file) {
    
    std::ifstream  f(file.c_str());

    std::string linia; 
    
    for (int y=7; y>-1; y--) {
        std::getline(f,linia);
        
        for (int x=0; x<8; x++) {
            board[x][y] = sign_to_object(linia[x]);
        }
    }
  

  f.close();
}
void checkboard::save_to_file(std::string&) {
    
}

void checkboard::print() {
    std::cout<<"\n"<<"   a b c d e f g h\n";

    for (int y=7; y>-1; y--) {
        std::cout<<"\n"<<y+1<<"  ";
        for (int x=0; x<8; x++) {
            std::cout<<board[x][y]->get_sign()<<" ";
             
        }
        std::cout<<" "<<y+1;
    }
    std::cout<<"\n\n"<<"   a b c d e f g h\n";
}



bool checkboard::is_another_figure_between(int  x1, int  x2, int  y1, int  y2) {
    if (x1 == x2){
       for (int y = std::min(y1, y2) + 1; y < std::max(y1, y2); y++ ) {
           if (board[x1][y]->get_sign() != '.') {
               return true;
           }
       } 
    } else if (y1 == y2){
       for (int x = std::min(x1, x2) + 1; x < std::max(x1, x2); x++ ) {
           if (board[x][y1]->get_sign() != '.') {
               return true;
           }
       }
    } else if (std::abs(x1 - x2) == std::abs(y1 - y2)) {
       for (int i =  1; i < std::abs(x1 - x2); i++ ) {
           if (board[std::min(x1, x2) + i][std::min(y1, y2) + i]->get_sign() != '.') {
               return true;
           } 
       }
    } else {
        return false;
    }
    return false;
}


int * checkboard::translate(std::string s){
   int t[4] ;
   t[0] = int(s[0]) - 97;
   t[1] = int(s[1]) - 49;
   t[2] = int(s[2]) - 97;
   t[3] = int(s[3]) - 49;
   return t;
}

bool checkboard::move(std::string s, figure::color who_moves) {
    int *table = translate(s);
    int x1 = table[0];
    int x2 = table[2];
    int y1 = table[1];
    int y2 = table[3];        
    //czy porusz się swoim
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
       if (board[x2][y2]->get_sign() == '.') {  
           if (board[x1][y1]->can_move(x1,x2,y1,y2)) { 
               figure * tmp;
               tmp = board[x2][y2];
               board[x2][y2] = board[x1][y1];
              
               board[x1][y1] = tmp;
               return true;
               
           } 
       } else {
           if (board[x1][y1]->can_capture(x1,x2,y1,y2) && board[x2][y2]->can_be_captured()) { 
               delete board[x2][y2];
               board[x2][y2] = board[x1][y1];
              
               board[x1][y1] = new empty(figure::none);
               return true;
           }     
       } 
    } 
       return false;
}



figure * checkboard::sign_to_object(char sign/*, figure::color c*/) {
    figure * f;
    //king * k = new king(figure::black);
    //return k;
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