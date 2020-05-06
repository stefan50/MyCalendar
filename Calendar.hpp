#ifndef CALENDAR_HPP
#define CALENDAR_HPP
#include "Event.hpp"
#include <ctime>
#include <cstdio>
#include "Vector.hpp"
#include <cstdlib>

class Calendar {
private:
    static const int DATE_BYTES = 11;
    Vector<Event> events;
    String date;
    struct DayBusiness {
        String date;
        String time;
    };
    int to_sec(int time_h) {
        return (time_h / 100) * 60 + (time_h % 100);
    }
    int to_hrs(int time_s) {
        int hrs = 0;
        while(time_s > 60) {
            hrs += 1;
            time_s -= 60;
        }
        return hrs * 100 + time_s;
    }
    void add_day(String& date) {
        int date_int = date.to_int();
        int day = date_int % 100;
        int month = (date_int / 100) % 100;
        int year = date_int / 10000;
        day++;
        if(month == 2) {
            if((year % 4 == 0 && year % 100 != 0) || (year % 100 == 0 && year % 400 == 0)) {
                if(day == 30) {
                    month++;
                    day = 1;
                }
            }
            if(day == 29) {
                day = 1;
                month++;
            }
        }
        if((month < 8 && month % 2 != 0) || (month >= 8 && month % 2 == 0)) {
            if(day == 32) {
                day = 1;
                month++;
            }
        }
        else {
            if(day == 31) {
                day = 1;
                month++;
            }
        }
        if(month == 13) {
            year++;
            month = 1;
        }
        char date_c[11];
        sprintf(date_c, "%d%d%d%d-%d%d-%d%d", year / 1000, (year / 100) % 10, (year / 10) % 10, year % 10, month / 10, month % 10, day / 10, day % 10);
        date = String(date_c);
    }
public:
    Calendar() {}
    Calendar(Vector<Event> events) {
        char current_date[DATE_BYTES];
        std::time_t timer = std::time(0);
        std::tm* now = std::localtime(&timer);
        sprintf(current_date, "%d-%d%d-%d%d", now->tm_year+1900, (now->tm_mon+1)/10, (now->tm_mon+1)%10, now->tm_mday/10, now->tm_mday%10);
        date = String(current_date);
        this->events = events;
    }

    void book(Event ev);
    void unbook(Event ev);
    void agenda(String date);
    void change(Event ev, String option, String new_value);
    void find(String key);
    Vector<DayBusiness> busydays(String start_date, String end_date);
    void holiday(String date);
    void find_slot(String date, int hours);
    void find_slot_with(String date, int hours, Vector<Calendar> calendars);
    /*void merge(Vector<Calendar> calendars);    */

    String get_current_date() const;
    int events_num() const {
        return events.get_size();
    }
    Event& operator[](int pos) {
        return events[pos];
    }
    friend std::ostream& operator<<(std::ostream& os, Calendar& cal);
};

#endif