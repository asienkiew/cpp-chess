/* 
 * File:   figure.cpp
 * Author: sienio
 * 
 * Created on 25 grudzień 2013, 15:09
 */

#include "figure.h"
#include <ctype.h>
figure::figure() {
  
}

figure::figure(color cc):c(cc) {
    jump_over = false;
    is_capturable = true;
   
}

figure::figure(const figure& orig) {
    sign = orig.sign;
    c = orig.c;
    jump_over = orig.jump_over;
}

figure::~figure() {
}
char figure::get_sign() {
    if (c == white) {
        return sign;    
    } else if (c == black){
        return tolower(sign);
    } else {
        return sign;
    }
    
};
char figure::get_sign_raw() {
    return sign;  
};

void figure::set_possible_moves_table() {
    
    for (unsigned char x1 = 0; x1 < 8; x1++) {  
        for (unsigned char y1 = 0; y1 < 8; y1++) {
            int_pair from = std::make_pair(x1, y1);
            for (unsigned char x2 = 0; x2 < 8; x2++) {

                for (unsigned char y2 = 0; y2 < 8; y2++) {
                    

                    int_pair to = std::make_pair(x2, y2);
                    std::vector<int_pair> empty_vector;
                    bool can_move_raw_var = this->can_move_raw(x1, x2, y1, y2);
                    bool can_capture_raw_var = this->can_capture_raw(x1, x2, y1, y2);
                    if (can_move_raw_var) {
                        if (possible_non_capture_moves.find(from) == possible_non_capture_moves.end()) {
                            possible_non_capture_moves[from] = empty_vector; 
                        }
                        possible_non_capture_moves[from].push_back(to);
                    }
                    if (can_capture_raw_var) {
                        if (possible_capture_moves.find(from) == possible_capture_moves.end()) {
                            possible_capture_moves[from] = empty_vector; 
                        }
                        possible_capture_moves[from].push_back(to);
                    }  
                    if (can_capture_raw_var || can_move_raw_var ) {
                        if (all_moves.find(from) == all_moves.end()) {
                            all_moves[from] = empty_vector; 
                        }
                        all_moves[from].push_back(to);    
                    }
                }            
            }           
        }   
    }
}
bool figure::can_capture_raw(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2) {
    return this->can_move_raw(x1, x2, y1, y2);
}

bool figure::can_capture(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2) {
    int_pair from = std::make_pair(x1, y1);
    int_pair to = std::make_pair(x2, y2);
    
    
    std::vector<int_pair> vec = possible_capture_moves.at(from);
    
    for (it_pair = vec.begin(); it_pair != vec.end(); ++it_pair) {  
        if (*it_pair == to) {
            return true;
        }
        
    }
    return false;
}

bool figure::can_move(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2) {
    int_pair from = std::make_pair(x1, y1);
    int_pair to = std::make_pair(x2, y2);
    
    std::vector<int_pair> vec = possible_non_capture_moves.at(from);
    
    for (it_pair = vec.begin(); it_pair != vec.end(); ++it_pair) {  
        if (*it_pair == to) {
            return true;
        }
        
    }
    return false;
}
std::vector <figure::int_pair> & figure::get_possible_moves_for_figure(int_pair & p) {
    return all_moves.find(p)->second;
}
 bool figure::can_jump_over(){
     return jump_over;
 }
 
 figure::color figure::get_color(){
     return c;
 }  
 
 bool figure::can_be_captured(){
     return is_capturable;
 }