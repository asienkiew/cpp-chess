#include <memory>
#include "gameplay.h"
#include "human.h"
#include "AI_tree.h"
#include "logger.h"

gameplay::gameplay(char * white_player_sign, char * black_player_sign, std::string file) {
    check = std::make_shared<checkboard>();
    players.resize(2);
    check->load_from_file(file);

    if (*white_player_sign == 'H') {
        players[figure::white] = std::make_unique<human>(figure::white, check);
    } else if (*white_player_sign == 'C') {
        players[figure::white] = std::make_unique<AI_tree>(figure::white, check, 3, 2);
    } else {
        throw "Sign should be H or C";
    }

    if (*black_player_sign == 'H') {
        players[figure::black] = std::make_unique<human>(figure::black, check);
    } else if (*black_player_sign == 'C') {
        players[figure::black] = std::make_unique<AI_tree>(figure::black, check, 3, 2);
    } else {
        throw "Sign should be H or C";
    }
}

void gameplay::start() {
    logger & logger_instance = logger::get_instance();
    logger_instance.log(players[0]->get_type() + " VS " + players[1]->get_type());
    check-> print();
    logger_instance.log(check->to_string());
    while (check->status == check->in_progress) {
        //clock_t t1 = clock();

        move m = this->players[check->who_is_next]->select_move();
        logger_instance.log(m.extended());
        //clock_t t2 = clock();
        //std::cout.precision(4);
        // std::cout<<std::fixed<<double(t2 - t1) / CLOCKS_PER_SEC;
        check->move_without_assert(m, true);
        check->print();
        logger_instance.log(check->to_string());
    }
    if (check->status == check->black_won) {
        std::cout << "\n***********************\n* Zwycięstwo czarnych *\n***********************\n";
        logger_instance.log("Black won\n");
    } else if (check->status == check->white_won) {
        std::cout << "\n**********************\n* Zwycięstwo białych *\n**********************\n";
        logger_instance.log("White won\n");
    } else if (check->status == check->draw) {
        std::cout << "\n**********************\n*******  Remis  ******\n**********************\n";
        logger_instance.log("Draw\n");
    } else {
        throw "Bad status";
    }

}


