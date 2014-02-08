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

const int AI_tree::H_TABLE_WHITE[8][8] = {
    {-20,-10, -10, 0, -5,-10,-10,-20},
    {-10,  0,  5,  0,  0,  0,  0,-10},
    {-10,  5,  5,  5,  5,  5,  0,-10},
    { -5,  0,  5,  5,  5,  5,  0, -5},
    { -5,  0,  5,  5,  5,  5,  0, -5},
    {-10,  0,  5,  5,  5,  5,  0,-10},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-20,-10,-10, -5, -5,-10,-10,-20}
};
const int AI_tree::H_TABLE_BLACK[8][8] = {
    {-20,-10,-10, -5, -5,-10,-10,-20},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-10,  0,  5,  5,  5,  5,  0,-10},
    { -5,  0,  5,  5,  5,  5,  0, -5},
    { -5,  0,  5,  5,  5,  5,  0, -5},
    {-10,  0,  5,  5,  5,  5,  5,-10},
    {-10,  0,  0,  0,  0,  5,  0,-10},
    {-20,-10,-10, -5,  0,-10,-10,-20}
};
const int AI_tree::W_TABLE_WHITE[8][8] = {
    { 0, -5, -5, -5, -5, -5,  5,  0},
    { 0,  0,  0,  0,  0,  0, 10,  0},
    { 0,  0,  0,  0,  0,  0, 10,  0},
    { 5,  0,  0,  0,  0,  0, 10,  0},
    { 5,  0,  0,  0,  0,  0, 10,  0},
    { 0,  0,  0,  0,  0,  0, 10,  0},
    { 0,  0,  0,  0,  0,  0, 10,  0},
    { 0, -5, -5, -5, -5, -5,  5,  0}
};
const int AI_tree::W_TABLE_BLACK[8][8] = {
    { 0,  5, -5, -5, -5, -5, -5,  0},
    { 0, 10,  0,  0,  0,  0,  0,  0},
    { 0, 10,  0,  0,  0,  0,  0,  0},
    { 0, 10,  0,  0,  0,  0,  0,  5},
    { 0, 10,  0,  0,  0,  0,  0,  5},
    { 0, 10,  0,  0,  0,  0,  0,  0},
    { 0, 10,  0,  0,  0,  0,  0,  0},
    { 0,  5, -5, -5, -5, -5, -5,  0}
};
const int AI_tree::G_TABLE_WHITE[8][8] = {
    {-20,-10,-10,-10,-10,-10,-10,-20},
    {-10,  5, 10,  0,  5,  0,  0,-10},
    {-10,  0, 10, 10,  5,  5,  0,-10},
    {-10,  0, 10, 10, 10, 10,  0,-10},
    {-10,  0, 10, 10, 10, 10,  0,-10},
    {-10,  0, 10, 10,  5,  5,  0,-10},
    {-10,  5, 10,  0,  5,  0,  0,-10},
    {-20,-10,-10,-10,-10,-10,-10,-20},
};
const int AI_tree::G_TABLE_BLACK[8][8] = {
    {-20,-10,-10,-10,-10,-10,-10,-20},
    {-10,  0,  0,  5,  0, 10,  5,-10},
    {-10,  0,  5,  5, 10, 10,  0,-10},
    {-10,  0, 10, 10, 10, 10,  0,-10},
    {-10,  0, 10, 10, 10, 10,  0,-10},
    {-10,  0,  5,  5, 10, 10,  0,-10},
    {-10,  0,  0,  5,  0, 10,  5,-10},
    {-20,-10,-10,-10,-10,-10,-10,-20},
};
const int AI_tree::S_TABLE_WHITE[8][8] = {
    {-50,-40,-30,-30,-30,-30,-40,-50},
    {-40,-20,  5,  0,  5,  0,-20,-40},
    {-30,  0, 10, 15, 15, 10,  0,-30},
    {-30,  5, 15, 20, 20, 15,  0,-30},
    {-30,  5, 15, 20, 20, 15,  0,-30},
    {-30,  0, 10, 15, 15, 10,  0,-30},
    {-40,-20,  5,  0,  5,  0,-20,-40},
    {-50,-40,-30,-30,-30,-30,-40,-50}
};
const int AI_tree::S_TABLE_BLACK[8][8] = {
    {-50,-40,-30,-30,-30,-30,-40,-50},
    {-40,-20,  0,  5,  0,  5,-20,-40},
    {-30,  0, 10, 15, 15, 10,  0,-30},
    {-30,  0, 15, 20, 20, 15,  5,-30},
    {-30,  0, 15, 20, 20, 15,  5,-30},
    {-30,  0, 10, 15, 15, 10,  0,-30},
    {-40,-20,  0,  5,  0,  5,-20,-40},
    {-50,-40,-30,-30,-30,-30,-40,-50}
};
const int AI_tree::P_TABLE_WHITE[8][8] = {
    {0,  0,  5,  0,  5, 10, 50,  0},
    {0, 10, -5,  0,  5, 10, 50,  0},
    {0, 10,-10,  0, 10, 20, 50,  0},
    {0,-20,  0, 20, 25, 30, 50,  0},
    {0,-20,  0, 20, 25, 30, 50,  0},
    {0, 10,-10,  0, 10, 20, 50,  0},
    {0, 10, -5,  0,  5, 10, 50,  0},
    {0,  0,  5,  0,  5, 10, 50,  0}
};
const int AI_tree::P_TABLE_BLACK[8][8] = {
    {0, 50, 10,  5,  0, -5,  0,  0},
    {0, 50, 10,  5,  0, -5, 10,  0},
    {0, 50, 20, 10,  0,-10, 10,  0},
    {0, 50, 30, 25, 20,  0,-20,  0},
    {0, 50, 30, 25, 20,  0,-20,  0},
    {0, 50, 20, 10,  0,-10, 10,  0},
    {0, 50, 10,  5,  0, -5, 10,  0},
    {0, 50, 10,  5,  0,  5,  0,  0}
};


#endif	/* AI_TREE_H */

