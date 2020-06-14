#ifndef EVENT_HPP
#define EVENT_HPP
#include <cstring>
#include "String.hpp"
#include <iostream>
#include "EventException.hpp"
#include "String.hpp"

class Event {
private:
    static const int DATE_BYTES = 11; //according to ISO 8601
    String date;
    String start_time;
    String end_time;
    String name;
    String note;
    void check_time(String time) {
        if(time.length() != 5 || time[2] != ':') {
            throw EventException("", time);
        }
        if(time.to_int() < 0 || time.to_int() > 2359) {
            throw EventException("", time);
        }
        for(int i = 0; i < time.length(); i++) {
            if(i == 2) continue;
            if(time[i] < '0' || time[i] > '9') {
                throw EventException("", time);
            }
        }
        if(time.to_int() % 100 > 59) {
            throw EventException("", time);
        }
        if(time.to_int() / 100 > 23) {
            throw EventException("", time);
        }
    }
    void check_date(String date) {
        Vector<String> date_by_parts = date.split('-');
        if(date.length() != 10 || date_by_parts[0].length() != 4 || date_by_parts[1].length() != 2 || date_by_parts[2].length() != 2) {
            throw EventException(date, "");
        }
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < date_by_parts[i].length(); j++) {
                if(date_by_parts[i][j] < '0' || date_by_parts[i][j] > '9') {
                    throw EventException(date, "");
                }
            }
        }
        if(date_by_parts[1].to_int() > 12) {
            throw EventException(date, "");
        }
        else {
            if(date_by_parts[1].to_int() == 2) {
                if((date_by_parts[0].to_int() % 4 == 0 && date_by_parts[0].to_int() % 100 != 0) || (date_by_parts[0].to_int() % 100 == 0 && date_by_parts[0].to_int() % 400 == 0)) {
                    if(date_by_parts[2].to_int() > 29) {
                        throw EventException(date, "");
                    }     
                }
                else if(date_by_parts[2].to_int() > 28) {
                    throw EventException(date, "");
                }
            }
            if(date_by_parts[1].to_int() < 7 && date_by_parts[1].to_int() % 2 == 0) {
                if(date_by_parts[2].to_int() > 31) {
                    throw EventException(date, "");
                }
            }
            if(date_by_parts[1].to_int() >= 7 && date_by_parts[1].to_int() % 2 != 0) {
                if(date_by_parts[2].to_int() > 30) {
                    throw EventException(date, "");
                }
            }
        }
    }
public:
    Event() {

    }

    Event(String date, String start_time, String end_time, String name, String note) {
        check_date(date);
        check_time(start_time);
        check_time(end_time);
        //std::cout << "Start: " << start_time.to_int() << " and end: " << end_time.to_int() << std::endl;
        if(start_time.to_int() > end_time.to_int()) {
            throw EventException(date, start_time);
        }
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
    String get_date() const;
    static bool compare_events(Event ev1, Event ev2);
    bool operator==(Event& other);
    bool operator!=(Event& other);
    friend std::istream& operator>>(std::istream& is, Event& ev);
    friend std::ostream& operator<<(std::ostream& os, const Event& ev);
};

#endif