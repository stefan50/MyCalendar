#include "Calendar.hpp"

String Calendar::get_current_date() const {
    return date;
}

int Calendar::book(Event ev) {
    return events.add_element(ev, Event::compare_events);
}

std::ostream& operator<<(std::ostream& os, Calendar& cal) {
    for(int i = 0; i < cal.events_num(); i++) {
        os << cal[i];
    }
    return os;
}
/*int unbook(Event ev);
void agenda(String date) const;
void change(String date, String start_time, String option, String new_value);
void find(String key) const;
int holiday(String date);
void find_slot(String date, int hours) const;
void find_slot_with(String date, int hours, Vector<Calendar> calendars) const;
void merge(Vector<Calendar> calendars); */