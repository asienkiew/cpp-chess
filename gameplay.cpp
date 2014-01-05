/* 
 * File:   gameplay.cpp
 * Author: sienio
 * 
 * Created on 5 styczeń 2014, 18:48
 */

#include "gameplay.h"

gameplay::gameplay() {
}

gameplay::gameplay(const gameplay& orig) {
}

gameplay::~gameplay() {
}
short int gameplay:: parse_command(std::string & command){
    if (command.length() != 4) {
        throw "BadSyntax";
    } 
    
}

