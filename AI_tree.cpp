#include "AI_tree.h"
#include "checkboard.h"
#include "figure.h"
#include <vector>
#include <map>
#include <cstdlib>
#include <utility>                   // for std::pair
#include <algorithm>
#include <iostream>
#include <fstream>
#include <thread>


#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

AI_tree::AI_tree(figure::color c, std::shared_ptr<checkboard> check, unsigned char var1, unsigned char var2) : AI(c, check) {
    is_endgame = false;
    MAX_DEPTH = var1;
    max_depth = MAX_DEPTH;
    add_depth = var2;
    type = "AI_tree";



}

move AI_tree::select_move() {
    srand(time(NULL));
    manage_is_end_game_flag();
    move chosen_move;

    func_call_counter = 0;

    possible_moves_0_level_to_score_map.clear();
    if (!possible_moves_0_level_stack.empty()) {
        throw "Error";
    }


    std::vector<move> possible_moves_0_level = get_possible_moves(*check);

    std::vector<move> best_moves;

    //tworzymy "mapę" z wektora wypełnioną tak jakby nullami
    for (unsigned i = 0; i < possible_moves_0_level.size(); ++i) {
        possible_moves_0_level_to_score_map.push_back(std::make_pair(possible_moves_0_level[i], SHORT_MAX_INT));
    }

    std::vector < move >::iterator it;
    std::vector<std::thread > threads;

    possible_moves_0_level_stack = std::stack<move, std::vector<move> > (possible_moves_0_level);

    unsigned number_of_threads = sysconf(_SC_NPROCESSORS_ONLN);

    if (number_of_threads == 0) {
        number_of_threads = 1;
    }
    for (unsigned i = 0; i < number_of_threads; i++) {

        threads.push_back(std::thread(&AI_tree::run_thread, this, std::ref(possible_moves_0_level_to_score_map), std::ref(possible_moves_0_level_stack)));
    }
    for (unsigned i = 0; i < number_of_threads; i++) {
        threads[i].join();
    }

    short int max = -SHORT_MAX_INT;

    for (unsigned i = 0; i < possible_moves_0_level_to_score_map.size(); ++i) {

        // std::cout<<possible_moves_0_level_to_score_map[i].first<<" "<<possible_moves_0_level_to_score_map[i].second<<"\n";
        int val = possible_moves_0_level_to_score_map[i].second;

        if (val == SHORT_MAX_INT) { // SHORT_MAX_INT to taki jakby null, nie powinno go być bo wątki powinn zamienić tego nulla na konkretne wartości
            throw "error";
        }
        if (val > max) {
            best_moves.clear();
            max = val;
        }

        if (val >= max) {
            best_moves.push_back(possible_moves_0_level_to_score_map[i].first);
        }


    }
    chosen_move = best_moves[rand() % best_moves.size()];

    std::cout << "Wybrany ruch to:\n";
    std::cout << chosen_move.raw() << "\n";
    //std::cout<<func_call_counter<<"\n";

    return chosen_move;
}

void AI_tree::run_thread(std::vector<move_int_pair> & scores_map, std::stack<move, std::vector<move> > & moves_stack) {
    int counter = 0;
    while (counter < 100) { //zabezpieczenie przed zapętleniem
        possible_moves_0_level_stack_mutex.lock();
        if (moves_stack.empty()) {
            possible_moves_0_level_stack_mutex.unlock();
            return;
        } else {

            move current_move = possible_moves_0_level_stack.top();
            possible_moves_0_level_stack.pop();
            possible_moves_0_level_stack_mutex.unlock();

            int current_value = get_value_for_move(current_move);

            for (unsigned i = 0; i < possible_moves_0_level_to_score_map.size(); ++i) {

                if (possible_moves_0_level_to_score_map[i].first == current_move &&
                        possible_moves_0_level_to_score_map[i].second == SHORT_MAX_INT) {
                    possible_moves_0_level_to_score_map[i].second = current_value;
                }
            }


        }
        counter++;
    }
}

int AI_tree::get_value_for_move(move m) {
    checkboard check_cp(*check);
    long_int_pair empty_pair = std::make_pair(SHORT_MAX_INT, SHORT_MAX_INT); // ma to odpowiadać za NULL
    graph g;
    vertex_t root = boost::add_vertex(empty_pair, g); //root
    check_cp.move_without_assert(m, true);
    int a = fill_possible_moves(g, root, check_cp, 1);
    g.clear();
    return a;
}

int AI_tree::fill_possible_moves(graph & g, vertex_t & parent_v, checkboard & checkb, int parent_depth) {
    long_int_pair empty_pair = std::make_pair(SHORT_MAX_INT, SHORT_MAX_INT); // ma to odpowiadać za NULL

    std::vector<move> possible_moves = get_possible_moves(checkb);


    std::vector < move >::iterator it;
    edge_t e;
    bool b;

    int current_depth = parent_depth + 1;


    if (possible_moves.empty()) {
        g[parent_v].first = g[parent_v].second = get_score(checkb);
        return g[parent_v].first;
    }


    for (unsigned int i = 0; i < possible_moves.size(); ++i) {
        /*
        possible_moves_0_level_stack_mutex.lock();
        func_call_counter++;
        possible_moves_0_level_stack_mutex.unlock();
         */
        move * it = &possible_moves[i];
        vertex_t current_v = boost::add_vertex(empty_pair, g);
        boost::tie(e, b) = boost::add_edge(parent_v, current_v, g);
        g[e] = *it;

        //std::cout<<it->which_was_captured;
        if ((current_depth >= max_depth && it->which_was_captured == '.') ||
                (current_depth >= max_depth + add_depth)) {

            g[current_v].first = g[current_v].second = get_score(checkb);
            ;

            continue;
        }
        checkb.move_without_assert(*it, true);

        fill_possible_moves(g, current_v, checkb, current_depth);
        checkb.revert_move_without_assert(*it, true);
    }

    short int max, min;
    min = SHORT_MAX_INT - 1;
    max = -min;

    short int vertex_value;

    out_edge_it out_i, out_end;

    if (current_depth % 2 == 1) {
        for (boost::tie(out_i, out_end) = out_edges(parent_v, g); out_i != out_end; ++out_i) {
            vertex_value = g[boost::target(*out_i, g)].first;
            if (vertex_value > max) {
                max = vertex_value;
            }
        }
    } else {
        for (boost::tie(out_i, out_end) = out_edges(parent_v, g); out_i != out_end; ++out_i) {
            vertex_value = g[boost::target(*out_i, g)].first;
            if (vertex_value < min) {
                min = vertex_value;
            }
        }
    }

    if (current_depth % 2 == 1) { //ja
        if (max > (SHORT_MAX_INT - 1 - 60)) {
            max -= 10;
        }
        if (max < (-SHORT_MAX_INT + 1 + 60)) {
            max += 10;
        }

        g[parent_v].first = max;
        //std::cout<<"max:"<<max<<"*\n";
    } else { // przeciwnik
        if (min > (SHORT_MAX_INT - 1 - 60)) {
            min -= 10;
        }
        if (min < (-SHORT_MAX_INT + 1 + 60)) {
            min += 10;
        }
        g[parent_v].first = min;



        //  std::cout<<"min:"<<min<<"*\n";
    }

    if (parent_depth == 1) {
        return g[parent_v].first;
    }
    return 0;

}

int AI_tree::evaluation_function(checkboard & check, figure::color player) {

    int score = 0;

    std::vector < int_pair >::iterator it_pair;


    for (it_pair = check.figures_position[player].begin(); it_pair != check.figures_position[player].end(); ++it_pair) {
        unsigned char x = it_pair->first;
        unsigned char y = it_pair->second;

        char sign = check.board[x][y]->get_sign_raw();

        switch (sign) {
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
                    if (!is_endgame) {
                        score += K_TABLE_WHITE_MIDDLEGAME[x][y];
                    } else {
                        score += K_TABLE_WHITE_ENDGAME[x][y];
                    }
                } else {
                    if (!is_endgame) {
                        score += K_TABLE_BLACK_MIDDLEGAME[x][y];
                    } else {
                        score += K_TABLE_BLACK_ENDGAME[x][y];
                    }
                }
                break;
        }
    }
    return score;
}

int AI_tree::simple_evaluation_function(checkboard & check, figure::color player) {

    int score = 0;
    std::vector < int_pair >::iterator it_pair;


    for (it_pair = check.figures_position[player].begin(); it_pair != check.figures_position[player].end(); ++it_pair) {
        unsigned char x = it_pair->first;
        unsigned char y = it_pair->second;

        char sign = check.board[x][y]->get_sign_raw();

        switch (sign) {
            case 'H':
                score += H_VALUE;
                break;
            case 'W':
                score += W_VALUE;
                break;
            case 'G':
                score += G_VALUE;
                break;
            case 'S':
                score += S_VALUE;
                break;
            case 'P':
                score += P_VALUE;
                break;
        }
    }
    return score;
}

int AI_tree::get_score(checkboard & check) {
    checkboard::STATUS status = check.status;
    short int max = SHORT_MAX_INT - 1;
    switch (status) {
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
            return -1; //minimalnie mnijesza od 0
        default:
            break;
    }
    float multiplier = 1.0;
    int score = evaluation_function(check, who) - evaluation_function(check, opposite);
    if (is_endgame) {
        score += get_king_distance_modifier(check);
    }



    move * last_move = &check.history.back();
    if (check.history.size() > 2) {
        if (check.history[check.history.size() - 1 - 2].is_opposite_to(*last_move)) {
            multiplier = is_endgame ? 0.5 : 0.9;
            if (check.history.size() > 4) {
                if (check.history[check.history.size() - 1 - 4] == (*last_move)) {
                    multiplier *= 0.8;
                    if (check.history.size() > 6) {
                        if (check.history[check.history.size() - 1 - 6].is_opposite_to(*last_move)) {
                            multiplier *= 0.7;
                        }
                    }
                }
            }
        }
    }



    return (short int) (multiplier * score);
}

int AI_tree::get_king_distance_modifier(checkboard & ch) {
    int my_score = simple_evaluation_function(ch, who);
    int his_score = simple_evaluation_function(ch, opposite);
    if (his_score < my_score) {
        return 6 * (4 - pow(ch.figures_position[who][0].first - ch.figures_position[opposite][0].first, 2)
                - pow(ch.figures_position[who][0].second - ch.figures_position[opposite][0].second, 2));

    } else {
        return 0;
    }

}

void AI_tree::manage_is_end_game_flag() {
    int s_w = simple_evaluation_function(*check, figure::white);
    int s_b = simple_evaluation_function(*check, figure::black);
    if (s_w < 600 && s_b < 600) {
        is_endgame = true;
        max_depth = MAX_DEPTH + 2;
    } else if (s_w < 1200 && s_b < 1200) {
        is_endgame = true;
        max_depth = MAX_DEPTH + 1;
    } else {
        is_endgame = false;
        max_depth = MAX_DEPTH;
    }


    //std::cout<<"*white:"<<evaluation_function(*check, figure::white)<<"*black:"<<  evaluation_function(*check, figure::black)<<"\n";
}
const short int AI_tree::SHORT_MAX_INT = std::numeric_limits<short int>::max();



const int AI_tree::H_TABLE_WHITE[8][8] = {
    {-20, -10, -10, 0, -5, -10, -10, -20},
    {-10, 0, 5, 0, 0, 0, 0, -10},
    {-10, 5, 5, 5, 5, 5, 0, -10},
    { -5, 0, 5, 5, 5, 5, 0, -5},
    { -5, 0, 5, 5, 5, 5, 0, -5},
    {-10, 0, 5, 5, 5, 5, 0, -10},
    {-10, 0, 0, 0, 0, 0, 0, -10},
    {-20, -10, -10, -5, -5, -10, -10, -20}
};
const int AI_tree::H_TABLE_BLACK[8][8] = {
    {-20, -10, -10, -5, -5, -10, -10, -20},
    {-10, 0, 0, 0, 0, 0, 0, -10},
    {-10, 0, 5, 5, 5, 5, 0, -10},
    { -5, 0, 5, 5, 5, 5, 0, -5},
    { -5, 0, 5, 5, 5, 5, 0, -5},
    {-10, 0, 5, 5, 5, 5, 5, -10},
    {-10, 0, 0, 0, 0, 5, 0, -10},
    {-20, -10, -10, -5, 0, -10, -10, -20}
};
const int AI_tree::W_TABLE_WHITE[8][8] = {
    { 0, -5, -5, -5, -5, -5, 5, 0},
    { 0, 0, 0, 0, 0, 0, 10, 0},
    { 0, 0, 0, 0, 0, 0, 10, 0},
    { 5, 0, 0, 0, 0, 0, 10, 0},
    { 5, 0, 0, 0, 0, 0, 10, 0},
    { 0, 0, 0, 0, 0, 0, 10, 0},
    { 0, 0, 0, 0, 0, 0, 10, 0},
    { 0, -5, -5, -5, -5, -5, 5, 0}
};
const int AI_tree::W_TABLE_BLACK[8][8] = {
    { 0, 5, -5, -5, -5, -5, -5, 0},
    { 0, 10, 0, 0, 0, 0, 0, 0},
    { 0, 10, 0, 0, 0, 0, 0, 0},
    { 0, 10, 0, 0, 0, 0, 0, 5},
    { 0, 10, 0, 0, 0, 0, 0, 5},
    { 0, 10, 0, 0, 0, 0, 0, 0},
    { 0, 10, 0, 0, 0, 0, 0, 0},
    { 0, 5, -5, -5, -5, -5, -5, 0}
};
const int AI_tree::G_TABLE_WHITE[8][8] = {
    {-20, -10, -10, -10, -10, -10, -10, -20},
    {-10, 5, 10, 0, 5, 0, 0, -10},
    {-10, 0, 10, 10, 5, 5, 0, -10},
    {-10, 0, 10, 10, 10, 10, 0, -10},
    {-10, 0, 10, 10, 10, 10, 0, -10},
    {-10, 0, 10, 10, 5, 5, 0, -10},
    {-10, 5, 10, 0, 5, 0, 0, -10},
    {-20, -10, -10, -10, -10, -10, -10, -20},
};
const int AI_tree::G_TABLE_BLACK[8][8] = {
    {-20, -10, -10, -10, -10, -10, -10, -20},
    {-10, 0, 0, 5, 0, 10, 5, -10},
    {-10, 0, 5, 5, 10, 10, 0, -10},
    {-10, 0, 10, 10, 10, 10, 0, -10},
    {-10, 0, 10, 10, 10, 10, 0, -10},
    {-10, 0, 5, 5, 10, 10, 0, -10},
    {-10, 0, 0, 5, 0, 10, 5, -10},
    {-20, -10, -10, -10, -10, -10, -10, -20},
};
const int AI_tree::S_TABLE_WHITE[8][8] = {
    {-50, -40, -30, -30, -30, -30, -40, -50},
    {-40, -20, 5, 0, 5, 0, -20, -40},
    {-30, 0, 10, 15, 15, 10, 0, -30},
    {-30, 5, 15, 20, 20, 15, 0, -30},
    {-30, 5, 15, 20, 20, 15, 0, -30},
    {-30, 0, 10, 15, 15, 10, 0, -30},
    {-40, -20, 5, 0, 5, 0, -20, -40},
    {-50, -40, -30, -30, -30, -30, -40, -50}
};
const int AI_tree::S_TABLE_BLACK[8][8] = {
    {-50, -40, -30, -30, -30, -30, -40, -50},
    {-40, -20, 0, 5, 0, 5, -20, -40},
    {-30, 0, 10, 15, 15, 10, 0, -30},
    {-30, 0, 15, 20, 20, 15, 5, -30},
    {-30, 0, 15, 20, 20, 15, 5, -30},
    {-30, 0, 10, 15, 15, 10, 0, -30},
    {-40, -20, 0, 5, 0, 5, -20, -40},
    {-50, -40, -30, -30, -30, -30, -40, -50}
};
const int AI_tree::P_TABLE_WHITE[8][8] = {
    {0, 0, 5, 0, 5, 10, 50, 0},
    {0, 10, -5, 0, 5, 10, 50, 0},
    {0, 10, -10, 0, 10, 20, 50, 0},
    {0, -20, 0, 20, 25, 30, 50, 0},
    {0, -20, 0, 20, 25, 30, 50, 0},
    {0, 10, -10, 0, 10, 20, 50, 0},
    {0, 10, -5, 0, 5, 10, 50, 0},
    {0, 0, 5, 0, 5, 10, 50, 0}
};
const int AI_tree::P_TABLE_BLACK[8][8] = {
    {0, 50, 10, 5, 0, -5, 0, 0},
    {0, 50, 10, 5, 0, -5, 10, 0},
    {0, 50, 20, 10, 0, -10, 10, 0},
    {0, 50, 30, 25, 20, 0, -20, 0},
    {0, 50, 30, 25, 20, 0, -20, 0},
    {0, 50, 20, 10, 0, -10, 10, 0},
    {0, 50, 10, 5, 0, -5, 10, 0},
    {0, 50, 10, 5, 0, 5, 0, 0}
};
const int AI_tree::K_TABLE_WHITE_MIDDLEGAME[8][8] = {
    { 20, 20, -10, -20, -30, -30, -30, -30},
    { 30, 20, -20, -30, -40, -40, -40, -40},
    { 10, 0, -20, -30, -40, -40, -40, -40},
    { 0, 0, -20, -40, -50, -50, -50, -50},
    { 0, 0, -20, -40, -50, -50, -50, -50},
    { 10, 0, -20, -30, -40, -40, -40, -40},
    { 30, 20, -20, -30, -40, -40, -40, -40},
    { 20, 20, -10, -20, -30, -30, -30, -30}
};
const int AI_tree::K_TABLE_BLACK_MIDDLEGAME[8][8] = {
    {-30, -30, -30, -30, -20, -10, 20, 20},
    {-40, -40, -40, -40, -30, -20, 20, 30},
    {-40, -40, -40, -40, -30, -20, 0, 10},
    {-50, -50, -50, -50, -40, -20, 0, 0},
    {-50, -50, -50, -50, -40, -20, 0, 0},
    {-40, -40, -40, -40, -30, -20, 0, 10},
    {-40, -40, -40, -40, -30, -20, 20, 30},
    {-30, -30, -30, -30, -20, -10, 20, 20}
};
const int AI_tree::K_TABLE_WHITE_ENDGAME[8][8] = {
    {-50, -30, -30, -30, -30, -30, -30, -50},
    {-30, -30, -10, -10, -10, -10, -30, -40},
    {-30, 0, 20, 30, 30, 20, -10, -30},
    {-30, 0, 30, 40, 40, 30, -10, -20},
    {-30, 0, 30, 40, 40, 30, -10, -20},
    {-30, 0, 20, 30, 30, 20, -10, -30},
    {-30, -30, -10, -10, -10, -10, -30, -40},
    {-50, -30, -30, -30, -30, -30, -30, -50}
};
const int AI_tree::K_TABLE_BLACK_ENDGAME[8][8] = {
    {-50, -30, -30, -30, -30, -30, -30, -50},
    {-30, -30, -10, -10, -10, -10, -30, -30},
    {-30, -10, 20, 30, 30, 20, 0, -30},
    {-20, -10, 30, 40, 40, 30, 0, -30},
    {-20, -10, 30, 40, 40, 30, 0, -30},
    {-30, -10, 20, 30, 30, 20, 0, -30},
    {-30, -30, -10, -10, -10, -10, -30, -30},
    {-50, -30, -30, -30, -30, -30, -30, -50}
};