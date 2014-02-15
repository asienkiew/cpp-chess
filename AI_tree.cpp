/* 
 * File:   AI_tree.cpp
 * Author: sienio
 * 
 * Created on 5 luty 2014, 21:39
 */

#include "AI_tree.h"
#include "checkboard.h"
#include "figure.h"
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
  #include <utility>                   // for std::pair
#include <algorithm>
      #include <iostream>
#include <fstream>

  #include <boost/graph/graph_traits.hpp>
  #include <boost/graph/adjacency_list.hpp>

#include <boost/graph/graphviz.hpp>

 

AI_tree::AI_tree(figure::color c, checkboard * check):AI(c, check) {
   
}

move AI_tree::select_move() {
 
    move chosen_move;
    int_pair empty_pair = std::make_pair(SHORT_MAX_INT,SHORT_MAX_INT); // ma to odpowiadać za NULL
    
    //std::cout<<SHORT_MAX_INT;
    
     srand (time(NULL));
 
    checkboard check_cp(check);
     //check->print();
     
    // check_cp.print();
     graph g;
    
    
    vertex_t root = boost::add_vertex(empty_pair,g); //root
    int zero = 0;
     fill_possible_moves(g, root, check_cp,zero, MAX_DEPTH);
    //boost::write_graphviz(std::cout, g);
     
    // typedef boost::graph_traits<graph>::vertex_iterator vertex_iter;
  //  std::pair<vertex_iter, vertex_iter> vp;
    //for (vp = boost::vertices(g); vp.first != vp.second; ++vp.first) {
       
    
    // std::cout <<g[*vp.first].first <<  " ";
   // }
    out_edge_it out_i, out_end;
    edge_t e, f;
    short int max = - SHORT_MAX_INT + 1;
    for (boost::tie(out_i, out_end) = out_edges(root, g); out_i != out_end; ++out_i) {
       
        // std::cout<<"\n"<<g[boost::target(*out_i, g)].first<<"\n";
        // std::cout<<"\n"<<g[*out_i];
        if ( g[boost::target(*out_i, g)].first > max) {
            max = g[boost::target(*out_i, g)].first;
            //std::cout<<g[e];
            chosen_move = g[*out_i];  
        }
        
    }
/*

  std::ofstream myfile;
  myfile.open ("g.txt");
      boost::write_graphviz(myfile, g);
      g.clear();
     std::cout<<"\n";*/
       std::cout<<chosen_move<<"\n";
    return chosen_move;
    
    // std::clock_t t1 = std::clock();
         
    
}

void AI_tree::fill_possible_moves(graph & g, vertex_t & parent_v, checkboard & check, int  parent_depth, int max_depth){
    static int counter = 0;
    
    const static int_pair empty_pair = std::make_pair(SHORT_MAX_INT,SHORT_MAX_INT); // ma to odpowiadać za NULL
    std::vector<move> possible_moves = get_possible_moves(check);
     

    std::vector < move >::iterator it;
    edge_t e; bool b;
    int current_depth = parent_depth + 2;
    if (parent_depth == 0) {
        counter = 0;
    } 

    if (possible_moves.empty()) {
        short int score  = get_score(check);
        g[parent_v].first = g[parent_v].second = score;
        return;
    }
    for(it = possible_moves.begin(); it != possible_moves.end(); ++it) {
        vertex_t current_v = boost::add_vertex(empty_pair,g);
        boost::tie(e,b) = boost::add_edge(parent_v,current_v,g);
        g[e] = *it;
        counter++;
        //std::cout<<it->which_was_captured;
        if((current_depth  >= max_depth && it->which_was_captured == '.') || 
                ( current_depth  >= max_depth +2 )) {
            short int score  = get_score(check);
            g[current_v].first = g[current_v].second = score;

            continue;
        }
        check.move_without_assert(*it, true);
        
        fill_possible_moves(g, current_v, check,current_depth, max_depth);
        check.revert_move_without_assert(*it, true);
    }
    short int max, min, extremum;
    min = SHORT_MAX_INT - 1;
    max = -min;
    
    out_edge_it out_i, out_end;
    
    for (boost::tie(out_i, out_end) = out_edges(parent_v, g); out_i != out_end; ++out_i) {
        short int vertex_value = g[boost::target(*out_i, g)].first;
            
        if ( vertex_value < min ) {
            min = vertex_value;
        }
        if ( vertex_value > max ) {
            max = vertex_value;
        }
    }
    if (current_depth % 2 == 1) { //ja
        if (max > (SHORT_MAX_INT - 1 - 60) ) {
            max -=10;
        }
        if (max < (-SHORT_MAX_INT + 1 + 60)) {
            max +=10;
        }  
        g[parent_v].first = max;  
        //std::cout<<"max:"<<max<<"*\n";
    } else {  // przeciwnik
        if (min > (SHORT_MAX_INT - 1 - 60) ) {
            min -=10;
        }
        if (min < (-SHORT_MAX_INT + 1 + 60)) {
            min +=10;
        }  
        g[parent_v].first = min; 
       //  std::cout<<"min:"<<min<<"*\n";
    }        
   


    if (parent_depth == 0 ) {
        std::cout<<counter<<"*";
    }
}

int AI_tree::evaluation_function(checkboard & check, figure::color player) {
    
    int score = 0;
    typedef std::pair<short int, short int> int_pair; 
     std::vector < int_pair >::iterator it_pair;

     
    for (it_pair = check.figures_position[player].begin(); it_pair != check.figures_position[player].end(); ++it_pair) {       
        short int x = it_pair->first;
        short int y = it_pair->second;

        char sign = check.board[x][y]->get_sign_raw();
  
        switch(sign) {
            case 'H':
                score += H_VALUE;
                if (player == figure::white) {
                    score += H_TABLE_WHITE[x][y];
                } else {
                    score += H_TABLE_BLACK[x][y]; 
                }
                break;
            case 'W':
                score += W_VALUE;
                if (player == figure::white) {
                    score += W_TABLE_WHITE[x][y];
                } else {
                    score += W_TABLE_BLACK[x][y]; 
                }
                break;
            case 'G':
                score += G_VALUE;
                if (player == figure::white) {
                    score += G_TABLE_WHITE[x][y];
                } else {
                    score += G_TABLE_BLACK[x][y]; 
                }
                break;
            case 'S':
                score += S_VALUE;
                if (player == figure::white) {
                    score += S_TABLE_WHITE[x][y];
                } else {
                    score += S_TABLE_BLACK[x][y]; 
                }
                break;
            case 'P':
                score += P_VALUE;
                if (player == figure::white) {
                    score += P_TABLE_WHITE[x][y];
                } else {
                    score += P_TABLE_BLACK[x][y]; 
                }
                break; 
            case 'K':
               
                if (player == figure::white) {
                    score += K_TABLE_WHITE_MIDDLEGAME[x][y];
                } else {
                    score += K_TABLE_BLACK_MIDDLEGAME[x][y]; 
                }
                break;                 
        }
    }
   
    return score;
    
   
}

int AI_tree::get_score(checkboard & check) {
    checkboard::STATUS status = check.status;
    short int max = SHORT_MAX_INT-1;
    switch(status) {
        case checkboard::black_won:
            if (who == figure::black) {
                return max;
            } else {
                return -max;
            }
              
        case checkboard::white_won:
             if (who == figure::black) {
                return -max;
            } else {
                return max;
            }
       case checkboard::draw:
           return 0;
       default:
           break; 
    }
    return evaluation_function(check, who) - evaluation_function(check,opposite);
}

const short int AI_tree::SHORT_MAX_INT =  std::numeric_limits<short int>::max();

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
const int AI_tree::K_TABLE_WHITE_MIDDLEGAME[8][8] = {
    { 20, 20,-10,-20,-30,-30,-30,-30},
    { 30, 20,-20,-30,-40,-40,-40,-40},
    { 10,  0,-20,-30,-40,-40,-40,-40},
    {  0,  0,-20,-40,-50,-50,-50,-50},
    {  0,  0,-20,-40,-50,-50,-50,-50},
    { 10,  0,-20,-30,-40,-40,-40,-40},
    { 30, 20,-20,-30,-40,-40,-40,-40},
    { 20, 20,-10,-20,-30,-30,-30,-30}
};
const int AI_tree::K_TABLE_BLACK_MIDDLEGAME[8][8] =  {
    {-30,-30,-30,-30,-20,-10, 20, 20},
    {-40,-40,-40,-40,-30,-20, 20, 30},
    {-40,-40,-40,-40,-30,-20,  0, 10},
    {-50,-50,-50,-50,-40,-20,  0,  0},
    {-50,-50,-50,-50,-40,-20,  0,  0},
    {-40,-40,-40,-40,-30,-20,  0, 10},
    {-40,-40,-40,-40,-30,-20, 20, 30},
    {-30,-30,-30,-30,-20,-10, 20, 20}        
};