#ifndef AI_TREE_H
#define AI_TREE_H
#include "AI.h"
#include "checkboard.h"
#include <mutex>
#include <stack>
#include <map>

#include <utility>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

class AI_tree : public AI {
public:
    move select_move();
    AI_tree(figure::color c, std::shared_ptr<checkboard>, unsigned char, unsigned char);

    int get_score(checkboard & check);

private:
    bool is_endgame;

    const static int H_VALUE = 900;
    const static int W_VALUE = 500;
    const static int G_VALUE = 330;
    const static int S_VALUE = 320;
    const static int P_VALUE = 100;
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

    typedef std::pair<int, int> long_int_pair;
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
    long_int_pair, move> graph;

    typedef boost::graph_traits<graph>::vertex_descriptor vertex_t;
    typedef boost::graph_traits<graph>::edge_descriptor edge_t;
    typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it;

    unsigned char MAX_DEPTH;
    unsigned char max_depth, add_depth;
    static const short int SHORT_MAX_INT;
    int func_call_counter;

    typedef std::pair<move, int> move_int_pair;

    std::vector<move_int_pair> possible_moves_0_level_to_score_map;

    std::stack<move, std::vector<move> > possible_moves_0_level_stack;
    std::mutex possible_moves_0_level_stack_mutex;

    int evaluation_function(checkboard & check, figure::color);
    int simple_evaluation_function(checkboard & check, figure::color);
    int get_king_distance_modifier(checkboard & check);
    int get_king_mobility(checkboard & check, figure::color);

    void manage_is_end_game_flag();
    int fill_possible_moves(graph & g, vertex_t & v, checkboard & check, int parent_depth);
    int get_value_for_move(move);
    void run_thread(std::vector<move_int_pair> &, std::stack<move, std::vector<move> > &);
};


#endif /* AI_TREE_H */

