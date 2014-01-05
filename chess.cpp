/* 
 * File:   chess.cpp
 * Author: sienio
 *
 * Created on 15 grudzień 2013, 22:32
 */

#include <cstdlib>
#include <iostream>
#include <map>
#include "checkboard.h"
#include "queen.h"
#include "bishop.h"
#include "rook.h"
#include "king.h"
#include "figure.h"

/*
 * 
 */


int main(int argc, char** argv) {

     checkboard chec;
     king k(figure::black);
     //std::cout<< k.can_capture(0,1,0,0);
     for (char c = 1; int (c) < 127; c++) {
         std::cout<<c<<" "<<int(c)<<"\n";
     }
     std::string s = "sample.chess";
     chec.load_from_file(s);
     chec.print();
     /*
     int * wsk = new int(3);
     delete wsk;
     std::cout<<*wsk;
     */
     
     std::cout << chec.move("a2a3", figure::white);
     chec.print();
     std::cout << chec.move("a3a4", figure::white);
     chec.print();
     std::cout << chec.move("a4a5", figure::white);
     chec.print();
     std::cout << chec.move("b1a2", figure::white);
     chec.print();
     std::cout << chec.move("c1b3", figure::white);
     chec.print();
     std::cout << chec.move("b3d4", figure::white);
     chec.print();
     
     std::cout << chec.move("d4f5", figure::white);
     chec.print();
     
     std::cout << chec.move("f5d6", figure::white);
     chec.print();
     
     std::cout << chec.move("d6e8", figure::white);
     chec.print();
     std::cout << chec.move("e7e6", figure::black);
     chec.print();
      std::cout << chec.move("e8e7", figure::black);
     chec.print();
      std::cout << chec.move("e7d6", figure::black);
     chec.print();
     
     //delete chec;
    int a = 1;

    return 0;
}