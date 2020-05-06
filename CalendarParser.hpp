#ifndef CALENDAR_PARSER_HPP
#define CALENDAR_PARSER_HPP
#include "String.hpp"
#include "Calendar.hpp"
#include <cstring>

class CalendarParser {
    String file;
    Calendar calendar;
public:
    void open(String file_name);
    void close();
    void save();
    void saveas(String new_file);
    void help();
    void run();
};

#endif 