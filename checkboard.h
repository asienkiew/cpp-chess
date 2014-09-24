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
#include "knight.h"
#include "rook.h"
#include "king.h"
#include "empty.h"
#include "bishop.h"


#include <map>
#include <string>
#include <vector>
#include <utility>

class checkboard {
    friend class AI;
    friend class AI_basic;
    friend class AI_tree;
public:
    figure *board[8][8];
    figure::color who_is_next;
    enum STATUS {draw, white_won, black_won, in_progress};
    STATUS status;
    void load_from_file(std::string &);
    void save_to_file(std::string &) ;
    void print() ;
    checkboard();
    checkboard(const checkboard& );

    checkboard& operator= (const checkboard& );
    virtual ~checkboard();
    bool move_from_string(std::string , figure::color );
    bool move_from_raw_coordinates(unsigned char, unsigned char, unsigned char, unsigned char, figure::color, char promote_to = 'H');
    move is_move_possible(unsigned char&,unsigned char&,unsigned char&,unsigned char&, figure::color&, char);

    bool is_stalemate(figure::color);
    bool is_checkmate(figure::color);
    bool is_any_move_possible(figure::color&);
    bool is_in_check(figure::color&);


    //do poprawy (powinno być private)
    bool move_without_assert(move, bool);

    void revert_last_two_moves();

    std::string to_string();

private:
     empty EMPTY;
      king KING_B, KING_W;
     queen QUEEN_B, QUEEN_W;
     rook  ROOK_B, ROOK_W;
     pawn  PAWN_B, PAWN_W;
     knight KNIGHT_B, KNIGHT_W;
     bishop BISHOP_B, BISHOP_W;

     void set_figures();

    typedef std::pair<unsigned char, unsigned char> int_pair;
    bool is_castling_possible[2];

    std::vector <std::vector <int_pair > > figures_position;

    void update_figures_position(int_pair &, figure::color , int_pair );

    bool revert_move_without_assert(move, bool);

    std::vector< move > history;
    figure * sign_to_object(char sign);
    bool is_another_figure_between(unsigned char,unsigned char,unsigned char,unsigned char);
    bool check_whether_castling_is_possible(bool, figure::color);
    bool is_under_attack_by_given(unsigned char &,unsigned char &,unsigned char &,unsigned char &, figure::color &);
    bool is_under_attack_by_any(unsigned char &, unsigned char &, figure::color&);
    bool will_be_in_check(move, bool opposite_player = false);
    void update_status();
    std::string serialize();
};

#endif	/* CHECKBOARD_H */