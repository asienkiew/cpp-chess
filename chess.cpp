/* 
 * File:   chess.cpp
 * Author: sienio
 *
 * Created on 15 grudzień 2013, 22:32
 */

#include <cstdlib>
#include <iostream>
#include <map>
#include "gameplay.h"

int main(int argc, char** argv) {
    
    try {
        gameplay * g;
        if (argc<3 || argc > 4) {
           std::cerr<<"There should be 2 or 3 arguments\n";
           return 0;  
        }          
        if (argc == 4) {
            if (access( argv[3], F_OK ) == -1) {
                std::cerr<<"Bad file\n";
                return 0;
            } 
            g = new gameplay(argv[1], argv[2], argv[3]);
        }
        if (argc == 3) {
            g = new gameplay(argv[1], argv[2]); 
        }
        
        ///
        g->start();   
        delete g;

    } catch(const char * w) {
        std::cout<<"Wyjatek: "<<w;
    }
    return 0;
}