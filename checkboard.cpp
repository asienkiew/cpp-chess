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
    std::cerr<<linia;
    for (int y=7; y>-1; y--) {
        std::getline(f,linia);
        std::cerr<<linia<<"\n";
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
            f = new   empty(figure::white);          
            break;
        default:
            throw "BadSign";
            break;
            //throw "sss";
           
    } 
    
}