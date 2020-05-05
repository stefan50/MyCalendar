#include "Calendar.hpp"

String Calendar::get_current_date() const {
    return date;
}

void Calendar::book(Event ev) {
    try {
        events.add_element(ev, Event::compare_events);
    } catch(int a) {
        std::cerr << "This event cannot be added!" << std::endl;
        events.remove_element(ev, Event::compare_events);
    }
}

std::ostream& operator<<(std::ostream& os, Calendar& cal) {
    for(int i = 0; i < cal.events_num(); i++) {
        os << cal[i];
    }
    return os;
}

void Calendar::unbook(Event ev) {
    events.remove_element(ev, Event::compare_events);
}

void Calendar::agenda(String date) {
    for(int i = 0; i < events.get_size(); i++) {
        if(events[i].get_date() == date)
            std::cout << events[i];
    }
}

void Calendar::change(Event ev, String option, String new_value) {
    Event curr_event = events.find_element(ev);
    unbook(curr_event);
    if(option == "date") {
        book(Event(new_value, curr_event.get_start_time(), curr_event.get_end_time(), curr_event.get_name(), curr_event.get_note()));
    }
    else if(option == "starttime") {
        book(Event(curr_event.get_date(), new_value, curr_event.get_end_time(), curr_event.get_name(), curr_event.get_note()));
    }
    else if(option == "enddate") {
        book(Event(curr_event.get_date(), curr_event.get_start_time(), new_value, curr_event.get_name(), curr_event.get_note()));
    }
    else if(option == "name") {
        book(Event(curr_event.get_date(), curr_event.get_start_time(), curr_event.get_end_time(), new_value, curr_event.get_note()));
    }
    else if(option == "note") {
        book(Event(curr_event.get_date(), curr_event.get_start_time(), curr_event.get_end_time(), curr_event.get_name(), new_value));
    }
}

void Calendar::find(String key) {
    for(int i = 0; i < events.get_size(); i++) {
        if(events[i].get_name().contains(key) || events[i].get_note().contains(key)) {
            std::cout << events[i];
        }
    }
}

/*void busydays(String start_date, String end_date);
int holiday(String date);
void find_slot(String date, int hours) const;
void find_slot_with(String date, int hours, Vector<Calendar> calendars) const;
void merge(Vector<Calendar> calendars); */