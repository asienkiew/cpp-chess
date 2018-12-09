#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <string>
#include <vector>
#include <memory>
#include "player.h"
#include "figure.h"
#include "checkboard.h"

class gameplay {
public:
    gameplay(char *, char *, std::string file = "samples/sample.chess");
    virtual ~gameplay() = default;
    void start();

private:
    std::shared_ptr<checkboard> check;
    std::vector< std::string > history;
    std::vector<std::unique_ptr<player>> players;
};

#endif /* GAMEPLAY_H */

