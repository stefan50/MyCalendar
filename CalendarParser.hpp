#ifndef CALENDAR_PARSER_HPP
#define CALENDAR_PARSER_HPP
#include "String.hpp"
#include "Calendar.hpp"
#include <cstring>

class CalendarParser {
    String file;
public:
    void open(String file_name);
};

#endif 