/* 
 * File:   logger.h
 * Author: sienio
 *
 * Created on July 24, 2014, 10:09 PM
 */

#ifndef LOGGER_H
#define	LOGGER_H

#include <fstream>

class logger {
public:
    
    static logger& get_instance();
    void log(const std::string&);
private:    
    std::ofstream log_file;
    logger(); 
    logger(const logger& orig);
    logger& operator=(const logger&);
    ~logger(); 
    

        

    
};

#endif	/* LOGGER_H */

