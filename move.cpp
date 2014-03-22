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
move::move(std::string s, figure::color who_moves) {
    
    
  
   x1 = int(s[0]) - 97;
   y1 = int(s[1]) - 49;
   x2 = int(s[2]) - 97;
   y2 = int(s[3]) - 49;
   c =  who_moves; 
   if (s.size() == 4) {
       promote_to = 'H'; 
   } else {
       promote_to = toupper(s[4]);    
   }
}

move::move(unsigned char x1, unsigned char x2,unsigned char y1,unsigned char y2, 
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
bool move::is_opposite_to(move& m ){
    return (this->x1 == m.x2 && this->y1 == m.y2 && this->x2 == m.x1 && this->y2 == m.y1 && 
            this->c == m.c &&
            this->is_valid && m.is_valid);
    
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
     os<<s<<":"<<m.which_moved<<"("<<(int)m.x1<<","<<(int)m.y1<<")->"<<m.which_was_captured<<"("<<(int)m.x2<<","<<(int)m.y2<<")"<<" "<<castling<<" "<<promotion<<" "<<enpassant;
     return os;
 }
 
 bool operator ==(move& m1, move& m2){
     return (m1.c == m2.c &&
         m1.x1 == m2.x1 &&
         m1.x2 == m2.x2 &&
         m1.y1 == m2.y1 &&
         m1.y2 == m2.y2 &&
         m1.which_moved == m2.which_moved &&
         m1.which_was_captured == m2.which_was_captured &&
         m1.is_castling == m2.is_castling &&
         m1.is_enpassant == m2.is_enpassant &&
         m1.is_promotion == m2.is_promotion 
             );
 }