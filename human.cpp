/* 
 * File:   human.cpp
 * Author: sienio
 * 
 * Created on 16 marzec 2014, 16:55
 */

#include "human.h"
#include <boost/regex.hpp>

human::human(figure::color c, checkboard * check):player(c, check) {
}

human::~human() {
}
bool human::is_command_ok(std::string s) {
    boost::regex rgx("^[a-h][1-8][a-h]([1-8]|8[whgs])$");
    if (!boost::regex_match(s, rgx)) { // 
        std::cout<<"Nieprawidłowy format komendy\n";
        return false;
    }  else {
        return true;
    }   
}
move human::select_move() {
         
    bool is_comm_ok;
    std::string command;
    move m;
    do {
         is_comm_ok = true;

         std::cin>>command;
         is_comm_ok = is_command_ok(command);
         
         if (is_comm_ok) {
             move m_tmp(command, who);
             m =  check->is_move_possible(m_tmp.x1, m_tmp.x2, m_tmp.y1, m_tmp.y2, m_tmp.c, m_tmp.promote_to);
             if (!m.is_valid) {
                 std::cout<<"Niedozwolony ruch\n";
             } 
         }

     } while (!m.is_valid || !is_comm_ok );
     return m;
}


