#include "CalendarParser.hpp"
#include <iostream>

void CalendarParser::open(const char* file_name) {
    int pos = 0;
    while(file_name[pos] != '.' && file_name[pos] != '\0') {
        pos++;
    }
    if(pos > 0 && !strcmp(file_name + pos, ".txt")) {
        BasicParser::open(file_name);
    }
    else {
        //invalid
        std::cout << "That's invalid" << std::endl;
    } 
}