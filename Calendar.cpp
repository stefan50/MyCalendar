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

void Calendar::busydays(String start_date, String end_date) {
    Vector<Event> busy_days;
    for(int i = 0; i < events.get_size(); i++) {
        if(events[i].get_date().to_int() >=  start_date.to_int() && events[i].get_date().to_int() <= end_date.to_int()) {
            if(events[i].get_name() != "Holiday") {
                busy_days.add_element(events[i], Event::compare_events);
            }
        }
    }
    Vector<DayBusiness> days;
    for(int i = 0; i < busy_days.get_size(); i++) {
        DayBusiness db;
        db.date = busy_days[i].get_date();
        int acc_time = 0;
        for(; busy_days[i].get_date() == db.date; i++) {
            int time = to_sec(busy_days[i].get_end_time().to_int()) - to_sec(busy_days[i].get_start_time().to_int());
            acc_time += time;
        }
        i--;
        acc_time = to_hrs(acc_time);
        char buf[6];
        sprintf(buf, "%d%d:%d%d", acc_time / 1000, (acc_time / 100) % 10, (acc_time / 10) % 10, acc_time % 10);
        db.time = String(buf);
        days.add_element(db, [](DayBusiness db1, DayBusiness db2) -> bool{return db1.time.to_int() > db2.time.to_int();});
    }

    for(int i = 0; i < days.get_size(); i++) {
        std::cout << days[i].date << " " << days[i].time << std::endl;
    }
}

void Calendar::holiday(String date) {
    book(Event(date, "00:00", "23:59", "Holiday", "You do not work on this day."));
}
/*void find_slot(String date, int hours) const;
void find_slot_with(String date, int hours, Vector<Calendar> calendars) const;
void merge(Vector<Calendar> calendars); */