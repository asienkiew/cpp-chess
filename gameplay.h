/* 
 * File:   gameplay.h
 * Author: sienio
 *
 * Created on 5 styczeń 2014, 18:48
 */

#ifndef GAMEPLAY_H
#define	GAMEPLAY_H
#include <string>
#include <vector>

class gameplay {
public:
    gameplay();
    gameplay(const gameplay& orig);
    virtual ~gameplay();
    short int parse_command(std::string &);
private:
    std::vector< std::string > history;
};

#endif	/* GAMEPLAY_H */

