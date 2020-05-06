#include "CalendarParser.hpp"
#include <iostream>
#include <fstream>

void CalendarParser::open(String file_name) {
    file = file_name;
    int pos = 0;
    while(file[pos] != '.' && file[pos] != '\0') {
        pos++;
    }
    if(pos > 0 && !strcmp(&file[pos], ".txt")) {
        //BasicParser::open(file_name);
        std::ifstream calendar_file(file.to_cstr());
        calendar_file >> calendar;
        std::cout << "Successfully opened " << file << std::endl;
        calendar_file.close();
    }
    else {
        //invalid
        std::cout << "That's invalid" << std::endl;
    } 
}

void CalendarParser::close() {
    std::cout << "Successfully closed " << file << std::endl;
    file = "";
}

void CalendarParser::save() {
    saveas(file);
}

void CalendarParser::saveas(String new_file) {
    std::ofstream calendar_file(new_file.to_cstr());
    calendar_file << calendar;
    std::cout << "Successfully saved " << new_file << std::endl;
    calendar_file.close();
}

void CalendarParser::help() {
    std::cout << "The following commands are supported:\nopen <file>\topens <file>\n" << 
    "close\tcloses currently opened file\n" <<
    "save\tsaves the currently open file\n" <<
    "saveas <file>\tsaves the currently open file in <file>\n" <<
    "help\tprints this information\n" <<
    "exit\texists the program\n";
}

void CalendarParser::run() {
    while(true) {
        std::cout << "> " << std::endl;
        char buffer[256];
        std::cin.getline(buffer, 256);
        
    }
}