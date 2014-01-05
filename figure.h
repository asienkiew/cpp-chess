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
    virtual bool can_move(int x1, int x2, int y1, int y2);
    virtual bool can_capture(int x1, int x2, int y1, int y2);
    virtual bool can_be_captured();
protected:
    bool jump_over;
    bool is_capturable;
    color c;

};

#endif	/* FIGURE_H */

