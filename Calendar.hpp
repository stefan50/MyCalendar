#ifndef CALENDAR_HPP
#define CALENDAR_HPP
#include "Event.hpp"
#include <ctime>
#include <cstdio>

class Calendar {
private:
    static const int DATE_BYTES = 11;
    Event* events;
    char* current_date;
public:
    Calendar(Event* events) {
        current_date = new char[DATE_BYTES];
        std::time_t timer = std::time(0);
        std::tm* now = std::localtime(&timer);
        sprintf(current_date, "%d-%d%d-%d%d", now->tm_year+1900, (now->tm_mon+1)/10, (now->tm_mon+1)%10, now->tm_mday/10, now->tm_mday%10);
    }

    const char* get_current_date() const;

    ~Calendar() {
        delete[] current_date;
    }
};

#endif