#ifndef QUEEN_H
#define QUEEN_H
#include "figure.h"

class queen : public figure {
public:

    queen(figure::color cc);
    virtual bool can_move_raw(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2);
    virtual ~queen() = default;
private:

};

#endif /* QUEEN_H */

