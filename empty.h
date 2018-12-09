#ifndef EMPTY_H
#define EMPTY_H
#include "figure.h"

class empty : public figure {
public:

    empty(figure::color cc);
    bool can_move_raw(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2);
    virtual ~empty() = default;
private:

};

#endif /* EMPTY_H */

