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
    
    enum status {draw, white_won, black_won, in_progress};
    status end_with;
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
    
    bool is_stalemate(figure::color);
    bool is_checkmate(figure::color);
    bool is_any_move_possible(figure::color&);
    bool is_in_check(figure::color&);
    
private:
    bool is_castling_possible[2];
    short int king_pos[2][2];

    bool execute_castling(move &);
    //std::map <char, std::vector<figure * > >
    bool move_without_assert(move, bool);
    bool revert_move_without_assert(move, bool);
    std::vector< move > history;
    short int * to_table(std::string );
    void push_move_to_history(short int,short int,short int,short int, figure::color, char, char);
    figure * sign_to_object(char sign); 
    bool is_another_figure_between(short int,short int,short int,short int);
    bool check_whether_castling_is_possible(bool, figure::color);
    bool is_under_attack(short int &,short int &,short int &,short int &, figure::color &);
    bool will_be_in_check(short int &,short int &,short int &,short int &, figure::color &);
};

#endif	/* CHECKBOARD_H */