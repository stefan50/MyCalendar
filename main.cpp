#include <iostream>
#include "CalendarParser.hpp"
#include <cstdio>

using namespace std;

int main() {
    /*CalendarParser cp;
    cp.open("test.txt");*/
    Event ev;
    Vector<Event> evs;
    for(int i = 0; i < 4; i++) {
        cin >> ev;
        evs.add_element(ev, Event::compare_events);
    }
    Calendar cal(evs);
    cin >> ev;
    cal.book(ev);
    cout << endl << cal << endl;
    //cout << cal << endl;
    /*for(int i = 0; i < evs.get_size(); i++) {
        cout << "Date: " << evs[i].get_date() << "Time: " << evs[i].get_start_time() << " " << evs[i].get_end_time() << endl;
    }*/
    /*for(int i = 0; i < 4; i++) {
        cout << evs[i] << endl;
    }*/
    return 0;
}