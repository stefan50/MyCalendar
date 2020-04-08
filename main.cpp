#include <iostream>
#include <ctime>
#include "Calendar.hpp"
#include <cstdio>

using namespace std;

int main() {
    //char t[50];
    //sprintf(t, "%d-%d%d-%d%d", 2020, 4/10 , 4, 8/10, 8);
    Calendar c(NULL);
    cout << c.get_current_date() << endl;
    //cout << t << endl;
    return 0;
}