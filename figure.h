#ifndef FIGURE_H
#define FIGURE_H

#include <string>
#include <utility>
#include <map>
#include <vector>

class figure {
public:
    char sign;

    enum color {
        black, white, none
    };
    typedef std::pair<unsigned char, unsigned char> int_pair;

    bool can_jump_over();
    color get_color();
    figure();
    figure(color);
    figure(const figure&);
    virtual ~figure() = default;
    char get_sign();
    char get_sign_raw();
    std::vector <int_pair> & get_possible_moves_for_figure(int_pair &);
    virtual bool can_move(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2);
    virtual bool can_capture(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2);

    virtual bool can_be_captured();
protected:
    virtual bool can_move_raw(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2) = 0;
    virtual bool can_capture_raw(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2);

    std::vector < int_pair >::iterator it_pair;
    void set_possible_moves_table();
    std::vector< std::vector< std::vector<int_pair> > >possible_non_capture_moves;
    std::vector< std::vector< std::vector<int_pair> > >possible_capture_moves;

    std::vector< std::vector< std::vector<int_pair> > >all_moves;
    bool can_capture_bool_table[8][8][8][8];
    bool can_move_bool_table[8][8][8][8];
    bool jump_over;
    bool is_capturable;
    color c;

};

#endif /* FIGURE_H */

