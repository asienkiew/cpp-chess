#ifndef ROOK_H
#define ROOK_H
#include "figure.h"

class rook : public figure {
public:
    rook(figure::color cc);
    virtual bool can_move_raw(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2);
    virtual ~rook() = default;
private:

};

#endif /* ROOK_H */

