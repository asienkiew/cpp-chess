/* 
 * File:   chess.cpp
 * Author: sienio
 *
 * Created on 15 grudzień 2013, 22:32
 */

#include <cstdlib>
#include <iostream>
#include <map>
#include <regex>


#include "checkboard.h"
#include "queen.h"
#include "bishop.h"
#include "rook.h"
#include "king.h"
#include "figure.h"
#include "AI.h"


int main(int argc, char** argv) {

     checkboard chec;
     king k(figure::black);
     //std::cout<< k.can_capture(0,1,0,0);
     /*for (char c = 1; int (c) < 127; c++) {
         std::cout<<c<<" "<<int(c)<<"\n";
     }*/
     std::string s = "sample.chess";
     chec.load_from_file(s);
     chec.print();
     /*
     int * wsk = new int(3);
     delete wsk;
     std::cout<<*wsk;
     */
      int x;
     //std::cout<<sizeof(x);
     AI ai_b(figure::black);
    //AI ai_w(figure::white);
     std::regex rgx("^[a-h][0-7][a-h][0-7]$", std::regex_constants::extended);
     
     bool is_move_ok ;
     bool is_command_ok;
     
     while (true) {

         do {
             is_move_ok = true;
             is_command_ok = true;
             
             std::string command;
             std::cin>>command;

             if (command.size() !=4) { // !std::regex_match(command, rgx)
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
     /*
     for (int i = 0; i <50 ; i++) {
         ai_b.select_move(chec);
         ai_w.select_move(chec);
         chec.print();
         
     }
*/
 
    // int * move = ai.select_move(chec);
     //std::cout <<"\n"<< move[0]<<" "<< move[1]<<" "<< move[2]<<" "<< move[3]<<" \n";
     
     /*
     std::cout << chec.move_from_string("a2a3", figure::white);
     chec.print();
     std::cout << chec.move_from_string("a3a4", figure::white);
     chec.print();
     std::cout << chec.move_from_string("a4a5", figure::white);
     chec.print();
     std::cout << chec.move_from_string("b1a2", figure::white);
     chec.print();
     std::cout << chec.move_from_string("c1b3", figure::white);
     chec.print();
     std::cout << chec.move_from_string("b3d4", figure::white);
     chec.print();
     
     std::cout << chec.move_from_string("d4f5", figure::white);
     chec.print();
     
     std::cout << chec.move_from_string("f5d6", figure::white);
     chec.print();
     
     std::cout << chec.move_from_string("d6e8", figure::white);
     chec.print();
     std::cout << chec.move_from_string("e7e6", figure::black);
     chec.print();
      std::cout << chec.move_from_string("e8e7", figure::black);
     chec.print();
      std::cout << chec.move_from_string("e7d6", figure::black);
     chec.print();
     
    */
    return 0;
}