#include "CalendarParser.hpp"
#include <iostream>
#include <fstream>

void CalendarParser::open(String file_name) {
    int pos = 0;
    while(file_name[pos] != '.' && file_name[pos] != '\0') {
        pos++;
    }
    if(pos > 0 && !strcmp(&file_name[pos], ".txt")) {
        //BasicParser::open(file_name);
        std::ifstream calendar_file(file_name.to_cstr(), std::ios::in);
    }
    else {
        //invalid
        std::cout << "That's invalid" << std::endl;
    } 
}