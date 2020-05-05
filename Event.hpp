#ifndef EVENT_HPP
#define EVENT_HPP
#include <cstring>
#include "String.hpp"
#include <iostream>

class Event {
private:
    static const int DATE_BYTES = 11; //according to ISO 8601
    String date;
    String start_time;
    String end_time;
    String name;
    String note;
public:
    Event(String date, String start_time, String end_time, String name, String note) {
        this->date = date;
        this->start_time = start_time;
        this->end_time = end_time;
        this->name = name;
        this->note = note;
    }

    String get_start_time() const;
    String get_end_time() const;
    String get_name() const;
    String get_note() const;
    friend std::istream& operator>>(std::istream& is, Event& ev);
    friend std::ostream& operator<<(std::ostream& os, Event& ev);
};

#endif