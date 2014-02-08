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
    int get_score(checkboard & check);
private:
    int evaluation_function(checkboard & check, figure::color);
    
    const static int H_VALUE = 900;
    const static int W_VALUE = 500;
    const static int G_VALUE = 330;
    const static int S_VALUE = 320;
    const static int P_VALUE = 100;
    const static int WIN = 5000;
    const static int DRAW = 0;
    const static int H_TABLE_WHITE[8][8];
    const static int H_TABLE_BLACK[8][8];
    const static int W_TABLE_WHITE[8][8];
    const static int W_TABLE_BLACK[8][8];
    const static int G_TABLE_WHITE[8][8];
    const static int G_TABLE_BLACK[8][8];
    const static int S_TABLE_WHITE[8][8];
    const static int S_TABLE_BLACK[8][8];    
    const static int P_TABLE_WHITE[8][8];
    const static int P_TABLE_BLACK[8][8];  
    const static int K_TABLE_WHITE_MIDDLEGAME[8][8];
    const static int K_TABLE_BLACK_MIDDLEGAME[8][8];  
    const static int K_TABLE_WHITE_ENDGAME[8][8];
    const static int K_TABLE_BLACK_ENDGAME[8][8];
    
};


#endif	/* AI_TREE_H */

