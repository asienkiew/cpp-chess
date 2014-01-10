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


int main(int argc, char** argv) {

     checkboard chec;
 
     std::string s = "sample.chess";
     chec.load_from_file(s);
     chec.print();

     AI ai_b(figure::black);
    //AI ai_w(figure::white);
     boost::regex rgx("^[a-h][1-8][a-h][1-8]$");
     
     bool is_move_ok ;
     bool is_command_ok;
    
     while (true) {

         do {
             is_move_ok = true;
             is_command_ok = true;
             
             std::string command;
             std::cin>>command;

             if (!boost::regex_match(command, rgx)) { // 
                 std::cout<<"Bad syntax\n";
                 is_command_ok = false;
             } else {
                 is_move_ok = chec.move_from_string(command, figure::white); 
                 if (!is_move_ok) {
                     std::cout<<"Illegal move\n";
                 } 
             }

         } while (!is_move_ok || !is_command_ok);
         chec.print();
         ai_b.select_move(chec);

         chec.print();
     }

    return 0;
}