#include "Calendar.hpp"

String Calendar::get_current_date() const {
    return date;
}

void Calendar::book(Event ev) {
    events.add_element(ev, Event::compare_events);
}

std::ostream& operator<<(std::ostream& os, Calendar& cal) {
    for(int i = 0; i < cal.events_num(); i++) {
        os << cal[i];
    }
    return os;
}

void Calendar::unbook(Event ev) {
    events.remove_element(ev);
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

Vector<Calendar::DayBusiness> Calendar::busydays(String start_date, String end_date) {
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
    return days;
}

void Calendar::holiday(String date) {
    Event ev(date, "00:00", "23:59", "Holiday", "You do not work on this day.");
    try {
        book(ev);
    } catch(EventException ex) {
        unbook(ev);
        std::cout << "There is a collision between events." << std::endl;
    }
}

void Calendar::find_slot(String date, int hours) {
    String curr_date = date;
    for(int i = 0;; i++) {
        int start_time = 800;
        if(i != 0) add_day(curr_date);
        while(start_time < 1700 && start_time + hours * 100 < 1700) {
            int end_time = start_time + hours * 100;
            char start_time_buf[6];
            char end_time_buf[6];
            sprintf(start_time_buf, "%d%d:%d%d", start_time / 1000, (start_time / 100) % 10, (start_time / 10) % 10, start_time % 10);
            sprintf(end_time_buf, "%d%d:%d%d", end_time / 1000, (end_time / 100) % 10, (end_time / 10) % 10, end_time % 10);
            Event test_ev(curr_date, String(start_time_buf), String(end_time_buf), "test", "test");
            try {
                events.add_element(test_ev, Event::compare_events);
            } catch(EventException& ex) {
                start_time += 1;
                events.remove_element(test_ev);
                continue;
            }
            events.remove_element(test_ev);
            std::cout << "Found slot: " << curr_date << " " << start_time_buf << " " << end_time_buf << std::endl;
            return;
        }
    }
}

void Calendar::find_slot_with(String date, int hours, Vector<Calendar> calendars) {
    String curr_date = date;
    while(true) {
        int start_time = 800;
        add_day(curr_date);
        while(start_time < 1700 && start_time + hours * 100 < 1700) {
            int end_time = start_time + hours * 100;
            char start_time_buf[6];
            char end_time_buf[6];
            sprintf(start_time_buf, "%d%d:%d%d", start_time / 1000, (start_time / 100) % 10, (start_time / 10) % 10, start_time % 10);
            sprintf(end_time_buf, "%d%d:%d%d", end_time / 1000, (end_time / 100) % 10, (end_time / 10) % 10, end_time % 10);
            Event test_ev(curr_date, String(start_time_buf), String(end_time_buf), "test", "test");
            try {
                events.add_element(test_ev, Event::compare_events);
                for(int i = 0; i < calendars.get_size(); i++) {
                    calendars[i].book(test_ev);
                }
            } catch(EventException& ex) {
                start_time += 1;
                events.remove_element(test_ev);
                for(int i = 0; i < calendars.get_size(); i++) {
                    calendars[i].unbook(test_ev);
                }
                continue;
            }
            events.remove_element(test_ev);
            for(int i = 0; i < calendars.get_size(); i++) {
                calendars[i].unbook(test_ev);
            }
            std::cout << "Found slot: " << curr_date << " " << start_time_buf << " " << end_time_buf << std::endl;
            return;
        }
    }
}
void Calendar::merge(Vector<Calendar> calendars) {
    for(int i = 0; i < calendars.get_size(); i++) {
        for(int j = 0; j < calendars[i].events_num(); j++) {
            try {
                events.add_element(calendars[i][j], Event::compare_events);
            } catch(EventException& ex) {
                std::cout << "There is a problem between event " << events.find_element(Event(ex.get_date(), ex.get_start_time(), "", "", ""))
                << " and event " << calendars[i][j] << std::endl;
                std::cout << "Which event would you like to change: ";
                int option;
                std::cin >> option;
                std::cout << "Enter new information for event:" << std::endl;
                Event ev;
                std::cin >> ev;
                if(option == 1) {
                    events.remove_element(events.find_element(Event(ex.get_date(), ex.get_start_time(), "", "", "")));    
                }
                else if(option == 2) {
                    events.remove_element(calendars[i][j]);
                }
                events.add_element(ev, Event::compare_events);
            }
        }
    }
}

std::istream& operator>>(std::istream& is, Calendar& cal) {
    Vector<Event> evs;
    Event ev;
    while(is >> ev) {
        evs.add_element(ev, Event::compare_events);
    }
    cal = Calendar(evs);
    return is;
}