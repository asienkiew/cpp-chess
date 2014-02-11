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

  #include <boost/graph/graph_traits.hpp>
  #include <boost/graph/adjacency_list.hpp>

#include <boost/graph/graphviz.hpp>

 

AI_tree::AI_tree(figure::color c, checkboard * check):AI(c, check) {
   
}

move AI_tree::select_move() {
 
   
    int_pair empty_pair = std::make_pair(SHORT_MAX_INT,SHORT_MAX_INT); // ma to odpowiadać za NULL
    
    //std::cout<<SHORT_MAX_INT;
    
     srand (time(NULL));
 
    // checkboard check_cp(*check);
     //check->print();
     
    // check_cp.print();
     graph g;
    
    
    vertex_t root = boost::add_vertex(empty_pair,g); //root
    int zero = 0;
     fill_possible_moves(g, root, *check,zero);
    //boost::write_graphviz(std::cout, g);
     
    // typedef boost::graph_traits<graph>::vertex_iterator vertex_iter;
  //  std::pair<vertex_iter, vertex_iter> vp;
    //for (vp = boost::vertices(g); vp.first != vp.second; ++vp.first) {
       
    
    // std::cout <<g[*vp.first].first <<  " ";
   // }
      out_edge_it out_i, out_end;
      edge_t e;
      for (boost::tie(out_i, out_end) = out_edges(root, g); 
           out_i != out_end; ++out_i) {
        e = *out_i;
         //   std::cout<<"\n"<<g[root].first<<"\n";
           // std::cout<<g[e];
        if ( g[boost::target(e, g)].first == g[root].first ) {
            std::cout<<"\n"<<g[root].first<<"\n";
            std::cout<<g[e];
            return g[e]; 
        }
        
      }
    
    
     std::clock_t t1 = std::clock();
         
    
 
    
  //  vertex v1(check.history.back());
   // vertex v2( possible_moves[0]); 
    // add_edge(check.history.back(), possible_moves[0], g);
    // boost::add_vertex(g,v1);
  /*  for(it = possible_moves.begin(); it != possible_moves.end(); ++it) {
      vertex_t v = boost::add_vertex(empty_pair,g);
      boost::tie(e,b) = boost::add_edge(root,v,g);
      g[e] = *it;
    }
    */
        // ...
/*
   // get the property map for vertex indices
    typedef boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;
    IndexMap index = boost::get(boost::vertex_index, g);
    
    
    std::cout << "vertices(g) = ";
    typedef boost::graph_traits<Graph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    for (vp = boost::vertices(g); vp.first != vp.second; ++vp.first) {
       
        check.move_without_assert(g[*vp.first], true);
        std::vector<move> possible_moves = get_possible_moves(check); 
      for(it = possible_moves.begin(); it != possible_moves.end(); ++it) {
      vertex_t v = boost::add_vertex(*it,g);
      boost::tie(e,b) = boost::add_edge(*vp.first,v,g);
      
     // g[e] = *it;
    }
        check.revert_move_without_assert(g[*vp.first], true);
      
    //std::cout <<g[*vp.first] <<  " ";
    //std::cout << std::endl;
    // ...
    }
    std::cout << "\n-- graphviz output START --" << std::endl;
    
    std::cout << "\n-- graphviz output END --" << std::endl;
 */
     //check.move_without_assert(possible_moves[0], true);
//    boost::write_graphviz(std::cout, g);
    
}

void AI_tree::fill_possible_moves(graph & g, vertex_t & parent_v, checkboard & check, int  parent_depth){
    static int counter = 0;
    
    const static int_pair empty_pair = std::make_pair(SHORT_MAX_INT,SHORT_MAX_INT); // ma to odpowiadać za NULL
    std::vector<move> possible_moves = get_possible_moves(check);
    //check.print();
    std::vector < move >::iterator it;
    edge_t e; bool b;
    int current_depth = parent_depth + 1;
   
    for(it = possible_moves.begin(); it != possible_moves.end(); ++it) {
        vertex_t current_v = boost::add_vertex(empty_pair,g);
        boost::tie(e,b) = boost::add_edge(parent_v,current_v,g);
        g[e] = *it;
        counter++;
        if(current_depth  >= MAX_DEPTH) {
            short int score  = get_score(check);
            g[current_v].first = g[current_v].second = score;
            //std::cout<<g[current_v].first<<"*\n";
           
            continue;
        }
        check.move_without_assert(*it, true);
        
        fill_possible_moves(g, current_v, check,current_depth);
        check.revert_move_without_assert(*it, true);
    }

    
     
            
            short int max, min;
            min = SHORT_MAX_INT - 1;
            max = -min;
            out_edge_it out_i, out_end;
            
            for (boost::tie(out_i, out_end) = out_edges(parent_v, g); 
                          out_i != out_end; ++out_i) {
                e = *out_i;

                if ( g[boost::target(e, g)].first < min ) {
                   min = g[boost::target(e, g)].first;
                }
                  if ( g[boost::target(e, g)].first > max ) {
                   max = g[boost::target(e, g)].first;
                }
            }
            if (current_depth % 2 == 1) { //ja
               g[parent_v].first = max;  
               //std::cout<<"max:"<<max<<"*\n";
            } else {  // przeciwnik
               g[parent_v].first = min; 
               //  std::cout<<"min:"<<min<<"*\n";
            }
            
      

    if (parent_depth == 0 ) {
        std::cout<<counter<<"*";
    }
}

int AI_tree::evaluation_function(checkboard & check, figure::color player) {
    
    int score = 0;
    for (short int i = 0; i< 16; i++) {
        short int x = check.figures_position[player][i][0];
        short int y = check.figures_position[player][i][1];
        if (x < 0 || y < 0) {
            continue;
        }
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

const int AI_tree::SHORT_MAX_INT =  std::numeric_limits<short int>::max();

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
