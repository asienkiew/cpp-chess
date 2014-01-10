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
#include "move.h"

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
    bool move_from_string(std::string , figure::color );
    bool move_from_raw_coordinates(short int, short int, short int, short int, figure::color);
    std::string to_string(short int *);
    bool is_move_possible(short int&,short int&,short int&,short int&, figure::color&);
    bool is_stalemate(figure::color&);
    bool is_checkmate(figure::color&);
    bool is_any_move_possible(figure::color&);
    bool is_check(figure::color&);
    
private:
    //std::map <char, std::vector<figure * > >
    bool move_without_assert(move m);
    std::vector< move > history;
    short int * to_table(std::string );
    void push_move_to_history(short int,short int,short int,short int, figure::color, char, char);
    figure * sign_to_object(char sign); 
    bool is_another_figure_between(short int,short int,short int,short int);
    bool check_whether_castling_is_possible(figure::color);

};

#endif	/* CHECKBOARD_H */