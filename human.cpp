#include "human.h"
#include <algorithm>
#include <string>

human::human(figure::color c, std::shared_ptr<checkboard> check) : player(c, check) {
    type = "Human";
}

bool human::is_command_ok(std::string s) {
    bool is_ok = true;
    //w funkcji jest implementacja ręczna regexpa ^[a-h][1-8][a-h]([1-8]|8[whgs])$
    // żeby nie dołączać biblioteki boost::regex co powoduje więcej problemów przy kompilacji
    if (!(s.size() == 4 || s.size() == 5)) {
        is_ok = false;
        return false;
    }

    if (!(97 <= int(s[0]) && int(s[0]) <= 104)) {
        is_ok = false;
    }
    if (!(49 <= int(s[1]) && int(s[1]) <= 56)) {
        is_ok = false;
    }
    if (!(97 <= int(s[2]) && int(s[2]) <= 104)) {
        is_ok = false;
    }
    if (!(49 <= int(s[3]) && int(s[3]) <= 56)) {
        is_ok = false;
    }
    if (s.size() == 5) {
        if (!((int(s[4]) == 'w' || int(s[4]) == 'h' || int(s[4]) == 'g' || int(s[4]) == 's') && s[3] == '8')) {
            is_ok = false;
        }
    }

    return is_ok;
}

move human::select_move() {

    bool is_comm_ok;
    std::string command;
    move m;
    do {
        is_comm_ok = true;

        std::cin>>command;

        if (command == "r") {
            check->revert_last_two_moves();
            check->print();
            is_comm_ok = false;
            continue;
        }

        std::transform(command.begin(), command.end(), command.begin(), ::tolower);
        is_comm_ok = is_command_ok(command);

        if (!is_comm_ok) {
            std::cout << "Nieprawidłowy format komendy\n";
        }
        if (is_comm_ok) {
            move m_tmp(command, who);
            m = check->is_move_possible(m_tmp.x1, m_tmp.x2, m_tmp.y1, m_tmp.y2, m_tmp.c, m_tmp.promote_to);
            if (!m.is_valid) {
                std::cout << "Niedozwolony ruch\n";
            }
        }

    } while (!m.is_valid || !is_comm_ok);
    return m;
}


