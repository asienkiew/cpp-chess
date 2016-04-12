/*
 * File:   logger.cpp
 * Author: sienio
 *
 * Created on July 24, 2014, 10:09 PM
 */

#include "logger.h"
#include <ctime>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <errno.h>

logger::logger() {
    int err = mkdir("./log", S_IRWXU );
    if (err != 0  && errno != EEXIST) throw "Cannot create log directory";
   
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime (buffer,80,"%d%m%Y_%H%M%S",timeinfo);
    std::string time_suffix(buffer);
    log_file.open("./log/"+ time_suffix);
}

logger::~logger() {
    this->log_file.close();
}
logger& logger::get_instance(){
    static logger instance;
    return instance;
}

void logger::log(const std::string & s) {
    log_file << s;
    log_file.flush();
}