#ifndef CALENDAR_PARSER_HPP
#define CALENDAR_PARSER_HPP
#include "BasicParser.hpp"
#include "Calendar.hpp"
#include <cstring>

class CalendarParser: public BasicParser {
public:
    void open(const char* file_name) override;
};

#endif 