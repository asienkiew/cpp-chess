/* 
 * File:   chess.cpp
 * Author: sienio
 *
 * Created on 15 grudzień 2013, 22:32
 */

#include <cstdlib>
#include <iostream>
#include <map>
#include <boost/regex.hpp>


#include "checkboard.h"
#include "queen.h"
#include "bishop.h"
#include "rook.h"
#include "king.h"
#include "figure.h"
#include "AI.h"
#include "AI_basic.h"


int main(int argc, char** argv) {

    checkboard chec;
    sizeof(chec);
     std::string s = argv[1];
     chec.load_from_file(s);
     chec.print();

     AI_basic ai_b(figure::black);
    //AI ai_w(figure::white);
     boost::regex rgx("^[a-h][1-8][a-h]([1-8]|8[whgs])$");
     
     bool is_move_ok ;
     bool is_command_ok;
     checkboard::status status = chec.in_progress;
     
     
     while (status == chec.in_progress) {

         do {
             is_move_ok = true;
             is_command_ok = true;
             
             std::string command;
             std::cin>>command;

             if (!boost::regex_match(command, rgx)) { // 
                 std::cout<<"Nieprawidłowy format komendy\n";
                 is_command_ok = false;
             } else {
                 is_move_ok = chec.move_from_string(command, figure::white); 
                 if (!is_move_ok) {
                     std::cout<<"Niedozwolony ruch\n";
                 } else {
                 if (chec.is_checkmate(figure::black)) {
                     status = chec.white_won;
                 }
                 if (chec.is_stalemate(figure::black)) {
                     status = chec.draw;
                 }
                 }
             }

         } while (!is_move_ok || !is_command_ok );
         chec.print();
         if (status == chec.in_progress) {
             
             ai_b.select_move(chec);

             chec.print();
             if (chec.is_checkmate(figure::white)) {
                 status = chec.black_won;
             }
             if (chec.is_stalemate(figure::white)) {
                 status = chec.draw;
             }
         }
     }
     
     if (status == chec.black_won) {
          std::cout<<"\n***********************\n* Zwycięstwo czarnych *\n***********************\n"; 
     } else if (status == chec.white_won) {
          std::cout<<"\n**********************\n* Zwycięstwo białych *\n**********************\n";  
     } else if (status == chec.draw) {
          std::cout<<"\n**********************\n*******  Remis  ******\n**********************\n"; 
     } else {
         throw "Bad status";
     }

    return 0;
}