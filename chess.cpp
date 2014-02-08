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
#include "figure.h"
#include "AI.h"
#include "AI_basic.h"
#include "AI_tree.h"


int main(int argc, char** argv) {

    checkboard chec;
    if (argc< 2) {
        std::cerr<<"No .chess file\n";
        return 0;
    }
     if (access( argv[1], F_OK ) == -1) {
         std::cerr<<"Bad file\n";
         return 0;
     } 
     std::string s = argv[1];
     chec.load_from_file(s);
     chec.print();

     AI_tree ai_b(figure::black);
    //AI ai_w(figure::white);
     boost::regex rgx("^[a-h][1-8][a-h]([1-8]|8[whgs])$");
     
     bool is_move_ok ;
     bool is_command_ok;
  
     
     
     while (chec.status == chec.in_progress) {

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
                 } 
             }

         } while (!is_move_ok || !is_command_ok );
         chec.print();
         if (chec.status == chec.in_progress) {
             
             ai_b.select_move(chec);

             chec.print();
        
         }
     }
     
     if (chec.status == chec.black_won) {
          std::cout<<"\n***********************\n* Zwycięstwo czarnych *\n***********************\n"; 
     } else if (chec.status == chec.white_won) {
          std::cout<<"\n**********************\n* Zwycięstwo białych *\n**********************\n";  
     } else if (chec.status == chec.draw) {
          std::cout<<"\n**********************\n*******  Remis  ******\n**********************\n"; 
     } else {
         throw "Bad status";
     }

    return 0;
}