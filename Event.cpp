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