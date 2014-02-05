/* 
 * File:   move.cpp
 * Author: sienio
 * 
 * Created on 7 styczeń 2014, 00:33
 */
#include <iostream>
#include <string>
#include "move.h"
#include "figure.h"

move::move() {
}
move::move(short int x1, short int x2,short int y1,short int y2, 
        figure::color c, char which_moved, char which_was_captured , char promote_to): 
            x1(x1), x2(x2), y1(y1), y2(y2), c(c), which_moved(which_moved), 
                  which_was_captured(which_was_captured), promote_to(promote_to) {
    
    is_valid = true;
    is_castling = false;
    is_enpassant = false;
    is_promotion = false;
    
}


move::~move() {
}
 std::ostream&  operator<< (std::ostream& os, move& m){
     std::string s;
     if (m.c == figure::black) {
         s = "black";
     } else {
         s = "white";
     }
     std:: string castling = m.is_castling ? "castling" : "";
     std:: string promotion = m.is_promotion ? "promotion" : "";
     std:: string enpassant = m.is_enpassant ? "enpassant" : "";
     os<<s<<":"<<m.which_moved<<"("<<m.x1<<","<<m.y1<<")->"<<m.which_was_captured<<"("<<m.x2<<","<<m.y2<<")"<<" "<<castling<<" "<<promotion<<" "<<enpassant;
     return os;
 }