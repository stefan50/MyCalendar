#ifndef EVENT_EXCEPTION_HPP
#define EVENT_EXCEPTION_HPP
#include <exception>
#include "Event.hpp"

class EventException: public std::exception {
private:
    String date;
    String start_time;
public:
    EventException(String date, String start_time) {
        this->date = date;
        this->start_time = start_time;
    }
    String get_date() {
        return date;
    }
    String get_start_time() {
        return start_time;
    }
};


#endif