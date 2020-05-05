#ifndef CALENDAR_HPP
#define CALENDAR_HPP
#include "Event.hpp"
#include <ctime>
#include <cstdio>
#include "Vector.hpp"

class Calendar {
private:
    static const int DATE_BYTES = 11;
    Vector<Event> events;
    String date;
public:
    Calendar(Event* events) {
        char current_date[DATE_BYTES];
        std::time_t timer = std::time(0);
        std::tm* now = std::localtime(&timer);
        sprintf(current_date, "%d-%d%d-%d%d", now->tm_year+1900, (now->tm_mon+1)/10, (now->tm_mon+1)%10, now->tm_mday/10, now->tm_mday%10);
        date = String(current_date);
    }

    String get_current_date() const;

    ~Calendar() {
        
    }
};

#endif