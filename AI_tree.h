/* 
 * File:   AI_tree.h
 * Author: sienio
 *
 * Created on 5 luty 2014, 21:39
 */

#ifndef AI_TREE_H
#define	AI_TREE_H
#include "AI.h"
#include "checkboard.h"

class AI_tree : public AI{
public:
     void select_move(checkboard & check);
    AI_tree(figure::color);
 
    virtual ~AI_tree();
private:
    float evaluation_function(checkboard & check);

};

#endif	/* AI_TREE_H */

