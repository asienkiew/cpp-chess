/* 
 * File:   AI_basic.cpp
 * Author: sienio
 * 
 * Created on 31 styczeń 2014, 23:19
 */

#include "AI_basic.h"
#include "AI.h"
#include "checkboard.h"
#include "figure.h"
#include <vector>
#include <cstdlib>

AI_basic::AI_basic(figure::color c):AI(c) {
}



AI_basic::~AI_basic() {
}

void AI_basic::select_move(checkboard & check){ 
 srand (time(NULL));
    std::vector <move> possible_moves;
    std::vector <move> checked_moves;
    std::vector <move> capture_attacker_moves; 
    std::vector <move> safe_captures_moves;
    std::vector <move> safe_moves;
    std::vector < move >::iterator it;
    
     for (short int x1 = 7; x1 > -1; x1--) {  
        for (short int x2 = 0; x2 < 8; x2++) {
            for (short int y1 = 0; y1 < 8; y1++) {
                for (short int y2 = 0; y2 < 8; y2++) {
                    move m = check.is_move_possible(x1, x2, y1, y2, who, 'H');
                    if (m.is_valid ) {
                       // check.print();
                        possible_moves.push_back(m);
                    }             
                }            
            }           
        }   
    }
    /*
    for (int i = 0 ; i<10000; i++) {
     for (short int x1 = 7; x1 > -1; x1--) {  
        for (short int x2 = 0; x2 < 8; x2++) {
            for (short int y1 = 0; y1 < 8; y1++) {
                for (short int y2 = 0; y2 < 8; y2++) {
                    move m = check.is_move_possible(x1, x2, y1, y2, who, 'H');
                 
                }            
            }           
        }   
    }
}
    */
    move last_move = check.history.back();
    std::cout<<"\nPossible moves:\n";
    
   it = possible_moves.begin(); 
   for(; it != possible_moves.end(); it++ ){
      std::cout<<*it<<"\n";
   } 
   
      it = possible_moves.begin(); 
   for(; it != possible_moves.end(); it++ ){
       check.move_without_assert(*it, false) ;
       if (check.is_in_check(last_move.c) && !check.is_under_attack_by_any(it->x2, it->y2, last_move.c) && check.history[check.history.size()-2].x2 !=it->x1 && check.history[check.history.size()-2].y2 !=it->y1 ) {
         checked_moves.push_back(*it);  
       }
       check.revert_move_without_assert(*it, false) ;

       
   } 
      std::cout<<"\nchecked_moves:\n";
      it = checked_moves.begin(); 
   for(; it != checked_moves.end(); it++ ){
      std::cout<<*it<<"\n";
   } 
      
      
      
         it = possible_moves.begin(); 
   for(; it != possible_moves.end(); it++ ){
       
       if (last_move.which_was_captured != '.' && (*it).x2 == last_move.x2 &&  (*it).y2 == last_move.y2 ) {
         capture_attacker_moves.push_back(*it);  
       }
       
   } 
      std::cout<<"\ncapture_attacker_moves:\n";
      it = capture_attacker_moves.begin(); 
   for(; it != capture_attacker_moves.end(); it++ ){
      std::cout<<*it<<"\n";
   }  
      
      
               it = possible_moves.begin(); 
   for(; it != possible_moves.end(); it++ ){
      
       if ( !check.is_under_attack_by_any(it->x2, it->y2, last_move.c) && it->which_was_captured !='.') {
         safe_captures_moves.push_back(*it);  
       }
       
   } 
      std::cout<<"\nsafe_captures_moves:\n";
      it = safe_captures_moves.begin(); 
   for(; it != safe_captures_moves.end(); it++ ){
      std::cout<<*it<<"\n";
   }  
      
            
               it = possible_moves.begin(); 
   for(; it != possible_moves.end(); it++ ){
      check.move_without_assert(*it, false) ;
       if ( check.is_under_attack_by_any((*it).x2, (*it).y2, who) /*|| ! check.is_under_attack_by_any((*it).x2, (*it).y2, last_move.c)*/) {
         safe_moves.push_back(*it);  
       }
       check.revert_move_without_assert(*it, false) ;
       
   } 
      std::cout<<"\nsafe_moves:\n";
      it = safe_moves.begin(); 
   for(; it != safe_moves.end(); it++ ){
      std::cout<<*it<<"\n";
   } 
      
    std::cout<<"***\n"; 
 
   if    (safe_captures_moves.size() > 0 ) {
       check.move_without_assert(safe_captures_moves[rand() % safe_captures_moves.size()], true);
       
       return;
   }   else if (capture_attacker_moves.size() > 0 ) {
       check.move_without_assert(capture_attacker_moves[rand() % capture_attacker_moves.size()], true);
       return;
    }   else if (checked_moves.size() > 0 ) {
     
        check.move_without_assert(checked_moves[rand() % checked_moves.size()], true) ;
      return;
   } else if  (safe_moves.size() > 0) {
   
       check.move_without_assert(safe_moves[rand() % safe_moves.size()], true);
       return;
       
   } else {
      
       check.move_without_assert(possible_moves[rand() % possible_moves.size()], true) ;
       return;
   }
}