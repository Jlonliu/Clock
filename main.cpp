#include <iostream>
#include "clock.h"

using namespace std;
using namespace susan;
int main(void)
{
    Clock clo(18, 19, 20);
    CalendarLite cal(1, 0, 0, 9, 1, 1);
    cal.reset(2023, 9, 9, 14, 54, 17);
    cout << "Time: " << clo << endl;
    cout << "Date: " << cal << endl;

    return 0;
}