#include <iostream>
#include <ctime>
#include "Calendar.hpp"
#include "Event.hpp"
#include <cstdio>

using namespace std;

int main() {
    //char t[50];
    //sprintf(t, "%d-%d%d-%d%d", 2020, 4/10 , 4, 8/10, 8);
    Calendar c(NULL);
    Event e("2020-02-01T17:20Z", "2020-02-02T02:00Z");
    Event e2("0000-00-00", "0000-00-00");
    e2 = e;
    cout << e.get_start_time() << endl;
    //cout << t << endl;
    return 0;
}