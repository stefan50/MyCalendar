#include "Event.hpp"

String Event::get_start_time() const {
    return start_time;
}

String Event::get_end_time() const {
    return end_time;
}

String Event::get_name() const {
    return name;
}

String Event::get_note() const {
    return note;
}

std::istream& operator>>(std::istream& is, Event& ev) {
    is >> ev.date >> ev.start_time >> ev.end_time;
    ev.name = "";
    ev.note = "";
    String s;
    int num;
    is >> num;
    for(int i = 0; i < num; i++) {
        is >> s;
        ev.name += s;
        if(i != num - 1) ev.name += " ";
    }
    is >> num;
    for(int i = 0; i < num; i++) {
        is >> s;
        ev.note += s;
        if(i != num - 1) ev.note += " ";
    }

    return is;
}


std::ostream& operator<<(std::ostream& os, const Event& ev) {
    os << ev.date << " " << ev.start_time << " "  << ev.end_time 
       << " " << ev.name.count_words() << " " << ev.name << " " << ev.note.count_words() 
       << " "<< ev.note << "\n";
    return os;
}

String Event::get_date() const {
    return date;
}

bool Event::compare_events(Event ev1, Event ev2) {
    if(ev1.get_date().to_int() < ev2.get_date().to_int()) return true;
    if(ev1.get_date().to_int() > ev2.get_date().to_int()) return false;
    if(ev1.get_start_time().to_int() >= ev2.get_start_time().to_int() && ev1.get_start_time().to_int() <= ev2.get_end_time().to_int()) throw EventException(ev2.get_date(), ev2.get_start_time());
    if(ev2.get_start_time().to_int() >= ev1.get_start_time().to_int() && ev2.get_start_time().to_int() <= ev1.get_end_time().to_int()) throw EventException(ev1.get_date(), ev1.get_start_time());
    if(ev1.get_end_time().to_int() >= ev2.get_start_time().to_int() && ev1.get_end_time().to_int() <= ev2.get_end_time().to_int()) throw EventException(ev1.get_date(), ev1.get_start_time());
    if(ev2.get_end_time().to_int() >= ev1.get_start_time().to_int() && ev2.get_end_time().to_int() <= ev1.get_end_time().to_int()) throw EventException(ev2.get_date(), ev2.get_start_time()); 
    if(ev1.get_end_time().to_int() < ev2.get_start_time().to_int() && ev1.get_start_time().to_int() < ev2.get_start_time().to_int()) return true;
    if(ev2.get_end_time().to_int() < ev1.get_start_time().to_int() && ev2.get_start_time().to_int() < ev1.get_start_time().to_int()) return false;
}

bool Event::operator!=(Event& other) {
    return !(date == other.get_date() && start_time == other.get_start_time() && end_time == other.get_end_time());
}

bool Event::operator==(Event& other) {
    return date == other.get_date() && start_time == other.get_start_time();
}
