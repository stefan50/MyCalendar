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
public:
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
    void busydays(String start_date, String end_date);
    void holiday(String date);
    /*void find_slot(String date, int hours) const;
    void find_slot_with(String date, int hours, Vector<Calendar> calendars) const;
    void merge(Vector<Calendar> calendars);    */

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