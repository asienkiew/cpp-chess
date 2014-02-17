/* 
 * File:   figure.h
 * Author: sienio
 *
 * Created on 25 grudzień 2013, 15:09
 */

#ifndef FIGURE_H
#define	FIGURE_H

#include <string>
#include <utility>
#include <map>
#include <vector>

class figure {
public:
    char sign;
    enum color {black, white, none};
    typedef std::pair<short int, short int> int_pair; 
    
    bool can_jump_over();
    color get_color();
    figure( );
    figure(color );
    figure(const figure& );
    virtual ~figure();
    char get_sign();
    char get_sign_raw();
    std::vector <int_pair> & get_possible_moves_for_figure(int_pair &);
    virtual bool can_move(short int x1, short int x2, short int y1, short int y2);
    virtual bool can_capture(short int x1, short int x2, short int y1, short int y2);

    virtual bool can_be_captured();
protected:
    virtual bool can_move_raw(short int x1, short int x2, short int y1, short int y2) = 0;
    virtual bool can_capture_raw(short int x1, short int x2, short int y1, short int y2);

    std::vector < int_pair >::iterator it_pair;
    void set_possible_moves_table();
    std::map <int_pair, std::vector<int_pair> > possible_non_capture_moves;
    std::map <int_pair, std::vector<int_pair> > possible_capture_moves;
        
    std::map <int_pair, std::vector<int_pair> > all_moves;

    bool jump_over;
    bool is_capturable;
    color c;

};

#endif	/* FIGURE_H */

