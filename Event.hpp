#ifndef EVENT_HPP
#define EVENT_HPP
#include <cstring>

class Event {
private:
    static const int DATE_BYTES = 11; //according to ISO 8601
    char* start_time;
    char* end_time;
public:
    Event(const char* start_time, const char* end_time) {
        this->start_time = new char[DATE_BYTES];
        this->end_time = new char[DATE_BYTES];
        strcpy(this->start_time, start_time);
        strcpy(this->end_time, end_time);
    }

    ~Event() {
        delete[] start_time;
        delete[] end_time;
    }

    const char* get_start_time() const;
    const char* get_end_time() const;

    Event& operator=(Event&);
};

#endif