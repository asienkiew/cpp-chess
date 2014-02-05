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
//#include "AI.h"


#include <map>
#include <string>
#include <vector>

class checkboard {
    friend class AI;
    friend class AI_basic;
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
    bool move_from_raw_coordinates(short int, short int, short int, short int, figure::color, char promote_to = 'H');
    move is_move_possible(short int&,short int&,short int&,short int&, figure::color&, char);
    
    bool is_stalemate(figure::color);
    bool is_checkmate(figure::color);
    bool is_any_move_possible(figure::color&);
    bool is_in_check(figure::color&);
    
private:
    bool is_castling_possible[2];
    short int king_pos[2][2];

 
    //std::map <char, std::vector<figure * > >
    bool move_without_assert(move, bool);
    bool put_figure(short int &, short int & ,figure::color &, char &);
    bool revert_move_without_assert(move, bool);
    std::vector< move > history;
    short int * to_table(std::string );
   
    figure * sign_to_object(char sign); 
    bool is_another_figure_between(short int,short int,short int,short int);
    bool check_whether_castling_is_possible(bool, figure::color);
    bool is_under_attack_by_given(short int &,short int &,short int &,short int &, figure::color &);
    bool is_under_attack_by_any(short int &, short int &, figure::color&);
    bool will_be_in_check(move, bool opposite_player = false);
};

#endif	/* CHECKBOARD_H */