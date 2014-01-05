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
    //delete chec;
    int a = 1;

    return 0;
}