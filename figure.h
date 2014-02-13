/* 
 * File:   figure.h
 * Author: sienio
 *
 * Created on 25 grudzień 2013, 15:09
 */

#ifndef FIGURE_H
#define	FIGURE_H

#include <string>

class figure {
public:
    char sign;
    enum color {black, white, none};
    
    bool can_jump_over();
    color get_color();
    figure( );
    figure(color );
    figure(const figure& );
    virtual ~figure();
    char get_sign();
    char get_sign_raw();
    virtual bool can_move(short int x1, short int x2, short int y1, short int y2) = 0;
    virtual bool can_capture(short int x1, short int x2, short int y1, short int y2);
    virtual bool can_be_captured();
protected:
    void set_possible_moves_table();
    bool possible_normal_moves[8][8][8][8];
    bool possible_capture_moves[8][8][8][8];
    bool jump_over;
    bool is_capturable;
    color c;

};

#endif	/* FIGURE_H */

