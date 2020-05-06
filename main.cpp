#include <iostream>
#include "CalendarParser.hpp"
#include <cstdio>

using namespace std;

int main() {
    /*CalendarParser cp;
    cp.open("test.txt");*/
    Event ev;
    Vector<Event> evs;
    for(int i = 0; i < 5; i++) {
        cin >> ev;
        evs.add_element(ev, Event::compare_events);
    }
    Calendar cal(evs);
    //cin >> ev;
    //cal.book(ev);
    //cal.unbook(ev);
    //cal.book(Event("18.05.2020", ev.get_start_time(), ev.get_end_time(), ev.get_name(), ev.get_note()));
    //cout << endl << cal << endl;
    Event event("2020-05-20", "12:20", "", "", "");
    cal.change(event, "date", "2020-05-18");
    //cal.find("Alo");
    cal.holiday("2020-05-17");
    cout << endl << cal << endl;
    cal.busydays("2020-05-17", "2020-05-22");
    //cal.book(Event("21.05.2020", "12:00", "12:20", "Meeting", "Important"));
    //cout << endl << cal << endl;
    //cout << cal << endl;
    /*for(int i = 0; i < evs.get_size(); i++) {
        cout << "Date: " << evs[i].get_date() << "Time: " << evs[i].get_start_time() << " " << evs[i].get_end_time() << endl;
    }*/
    /*for(int i = 0; i < 4; i++) {
        cout << evs[i] << endl;
    }*/
    return 0;
}