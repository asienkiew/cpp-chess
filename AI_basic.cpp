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
#include <ctime>

AI_basic::AI_basic(figure::color c, checkboard * check):AI(c, check) {
    type = "AI_basic";
}


move AI_basic::select_move(){
    srand (time(NULL));

    checkboard check_cp = *check;
    std::vector <move> possible_moves;
    std::vector <move> checked_moves;
    std::vector <move> capture_attacker_moves;
    std::vector <move> safe_captures_moves;
    std::vector <move> safe_moves;
    std::vector < int_pair >::iterator it_pair;
    std::vector < move >::iterator it;
     std::clock_t t1 = std::clock();

    for (it_pair = check_cp.figures_position[who].begin(); it_pair != check_cp.figures_position[who].end(); ++it_pair) {
        unsigned char x1 = it_pair->first;
        unsigned char y1 = it_pair->second;
        for (unsigned char x2 = 0; x2 < 8; x2++) {
            for (unsigned char y2 = 0; y2 < 8; y2++) {

                move m = check_cp.is_move_possible(x1, x2, y1, y2, who, 'H');
                if (m.is_valid ) {
                   // check_cp.print();
                    possible_moves.push_back(m);
                }
            }
        }

    }
      std::clock_t t2 = std::clock();
    /*




    for (int i = 0 ; i<10000; i++) {
     for (unsigned char x1 = 7; x1 > -1; x1--) {
        for (unsigned char x2 = 0; x2 < 8; x2++) {
            for (unsigned char y1 = 0; y1 < 8; y1++) {
                for (unsigned char y2 = 0; y2 < 8; y2++) {
                    move m = check_cp.is_move_possible(x1, x2, y1, y2, who, 'H');

                }
            }
        }
    }
}

        for (int i = 0 ; i<10000; i++) {
 for (unsigned char i = 0; i < 16; i++) {
        unsigned char x1 = check_cp.figures_position[who][i][0];
        unsigned char y1 = check_cp.figures_position[who][i][1];
        if (x1 > -1 && y1 > -1) {
            for (unsigned char x2 = 0; x2 < 8; x2++) {
                for (unsigned char y2 = 0; y2 < 8; y2++) {

                    move m = check_cp.is_move_possible(x1, x2, y1, y2, who, 'H');

                }
            }
        }
    }
}
   */
    std::clock_t t3 = std::clock();
    std::cout.precision(15);
     std::cout<<std::fixed<<double(t2 - t1) / CLOCKS_PER_SEC<<" "<<double(t3 - t2) / CLOCKS_PER_SEC;

     move last_move = check_cp.history.back();
    std::cout<<"\nPossible moves:\n";

   it = possible_moves.begin();
   for(; it != possible_moves.end(); it++ ){
      std::cout<<*it<<"\n";
   }

      it = possible_moves.begin();
   for(; it != possible_moves.end(); it++ ){
       check_cp.move_without_assert(*it, false) ;
       if (check_cp.is_in_check(last_move.c) && !check_cp.is_under_attack_by_any(it->x2, it->y2, last_move.c) && check_cp.history[check_cp.history.size()-2].x2 !=it->x1 && check_cp.history[check_cp.history.size()-2].y2 !=it->y1 ) {
         checked_moves.push_back(*it);
       }
       check_cp.revert_move_without_assert(*it, false) ;


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

       if ( !check_cp.is_under_attack_by_any(it->x2, it->y2, last_move.c) && it->which_was_captured !='.') {
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
      check_cp.move_without_assert(*it, false) ;
       if ( check_cp.is_under_attack_by_any((*it).x2, (*it).y2, who) /*|| ! check_cp.is_under_attack_by_any((*it).x2, (*it).y2, last_move.c)*/) {
         safe_moves.push_back(*it);
       }
       check_cp.revert_move_without_assert(*it, false) ;

   }
      std::cout<<"\nsafe_moves:\n";
      it = safe_moves.begin();
   for(; it != safe_moves.end(); it++ ){
      std::cout<<*it<<"\n";
   }

    std::cout<<"***\n";

   if        (safe_captures_moves.size() > 0 ) {
      return safe_captures_moves[rand() % safe_captures_moves.size()];
   } else if (capture_attacker_moves.size() > 0 ) {
       return capture_attacker_moves[rand() % capture_attacker_moves.size()];
   } else if (checked_moves.size() > 0 ) {
      return checked_moves[rand() % checked_moves.size()];
   } else if (safe_moves.size() > 0) {
      return safe_moves[rand() % safe_moves.size()];
   } else {
      return possible_moves[rand() % possible_moves.size()];
   }
}