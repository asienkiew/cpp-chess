#ifndef KING_H
#define KING_H
#include "figure.h"

class king : public figure {
public:
    king(figure::color cc);
    virtual bool can_move_raw(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2);
    virtual bool can_capture_raw(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2);
private:

};

#endif /* KING_H */

