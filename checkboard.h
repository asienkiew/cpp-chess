/* 
 * File:   checkboard.h
 * Author: sienio
 *
 * Created on 15 grudzień 2013, 22:34
 */

#ifndef CHECKBOARD_H
#define	CHECKBOARD_H

#include "figure.h"
#include "pawn.h"
#include "queen.h"

#include <map>
#include <string>
#include <vector>

class checkboard {
public:
    figure *board[8][8];
    void load_from_file(std::string &);
    void save_to_file(std::string &) ;  
    void print() ; 
    checkboard();
    //checkboard(const checkboard& orig);
    virtual ~checkboard();
    bool move(std::string , figure::color );
    bool move_from_raw_coordinates(int, int, int, int, figure::color);
    std::string to_string(int *);
private:
    std::vector< int * > history;
    int * to_table(std::string );
    
    figure * sign_to_object(char sign/*, figure::color c*/); 
    bool is_another_figure_between(int,int,int,int);
    //static std::string b = "black";
     //= new pawn("black"); 
   
    //static const  p_b = pawn("black"); 
    //static const  p_b = pawn("black"); 
};

#endif	/* CHECKBOARD_H */