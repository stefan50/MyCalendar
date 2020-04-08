#include "Event.hpp"

const char* Event::get_start_time() const {
    return start_time;
}

const char* Event::get_end_time() const {
    return end_time;
}

Event& Event::operator=(Event& e) {
    strcpy(this->start_time, e.get_start_time());
    strcpy(this->end_time, e.get_end_time());
    return *this;
}