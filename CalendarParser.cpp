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
        std::fstream calendar_file;
        calendar_file.open(file.to_cstr(), std::ios::out | std::ios::app);
        calendar_file.close();
        calendar_file.open(file.to_cstr(), std::ios::in);
        if(calendar_file) {
            calendar_file >> calendar;
            std::cout << "Successfully opened " << file << std::endl;
        }
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
        std::cout << "> ";
        char buffer[256];
        std::cin.getline(buffer, 256);
        Vector<String> command = String(buffer).split(' ');
        if(command[0] == "open") {
            open(command[1]);
        }
        else if(command[0] == "close") {
            close();
        }
        else if(command[0] == "save") {
            save();
        }
        else if(command[0] == "saveas") {
            saveas(command[1]);
        }
        else if(command[0] == "help") {
            help();
        }
        else if(command[0] == "exit") {
            std::cout << "Exiting the program..." << std::endl;
            break;
        }
        else if(command[0] == "book") {
            Event ev;
            try {
                ev = Event(command[1], command[2], command[3], command[5], command[7]);
                calendar.book(ev);
            } catch(EventException ex) {
                calendar.unbook(ev);
                if(ex.get_date() == "") {
                    std::cout << ex.get_start_time() << " is not in the desired format!" << std::endl;
                }
                else if(ex.get_start_time() == "") {
                    std::cout << ex.get_date() << " is not in the desired format!" << std::endl;
                }
                else {
                    std::cout << "There is a collision between events." << std::endl;
                }
            }
        }
        else if(command[0] == "unbook") {
            calendar.unbook(Event(command[1], command[2], command[3], "", ""));
        }
        else if(command[0] == "agenda") {
            calendar.agenda(command[1]);
        }
        else if(command[0] == "change") {
            Event ev(command[1], command[2], "", "", "");
            calendar.change(ev, command[3], command[4]);
        }
        else if(command[0] == "find") {
            calendar.find(command[1]);
        }
        else if(command[0] == "holiday") {
            calendar.holiday(command[1]);
        }
        else if(command[0] == "busydays") {
            calendar.busydays(command[1], command[2]);
        }
        else if(command[0] == "findslot") {
            calendar.find_slot(command[1], command[2].to_int());
        }
        else if(command[0] == "findslotwith") {
            Vector<Calendar> calendars;
            for(int i = 3; i < command.get_size(); i++) {
                Calendar cal;
                std::ifstream cal_file;
                cal_file.open(command[i].to_cstr());
                cal_file >> cal;
                cal_file.close();
                calendars.add_element(cal, [](Calendar c1, Calendar c2) -> bool{return c1.events_num() > c2.events_num();});
            }
            calendar.find_slot_with(command[1], command[2].to_int(), calendars);
        }
        else if(command[0] == "merge") {
            Vector<Calendar> calendars;
            for(int i = 1; i < command.get_size(); i++) {
                Calendar cal;
                std::ifstream cal_file;
                cal_file.open(command[i].to_cstr());
                cal_file >> cal;
                cal_file.close();
                calendars.add_element(cal, [](Calendar c1, Calendar c2) -> bool{return c1.events_num() > c2.events_num();});
            }
            calendar.merge(calendars);
        }
        else {
            std::cout << "Invalid command!" << std::endl;
        }
    }
}