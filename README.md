## 简介(Brief)
- 这是一个用来显示时间或日期的类。还支持一些时间的运算。虽然有些运算对于时间来说毫无意义，但是还是实现了出来。
- This is a class used to display time or date. It also supports some time functions. Although some functions are meaningless for time, they are still written.
## 用法(Usage)
- 时间类Clock的用法(Usage of Clock)
```cpp
#include <iostream>
#include "clock.h"

using namespace std;
using namespace susan;
int main(void)
{
    Clock clock1;//创建一个时钟对象(Create a clock object)
    int second = 777;//秒(Second)
    clock2 = Clock(second);//强制类型转换(Forced type conversion)
    second = int(clock2);//反向强制类型转换(Reverse forced type conversion)
    clock1.reset(12, 34, 56); //重置时间(Reset time)
    clock.hour();//获取小时(Get hour)
    clock.minute();//获取分钟(Get minute)
    clock.second();//获取秒(Get second)
    clock1+=clock2;//时间相加(Add time)
    clock1-=clock2;//时间相减(Subtract time)
    clock3=clock1+clock2;//时间相加(Add time)
    clock4=clock1-clock2;//时间相减(Subtract time)
    clock1<clock2;//时间比较(Compare time)
    clock1>clock2;//时间比较(Compare time)
    clock1<=clock2//时间比较(Compare time)
    clock1>=clock2//时间比较(Compare time)
    cout<<clock1<<endl;//显示时间(Display time)
    
｝
```
- 日期类CalendarLite的用法(Usage of CalendarLite)
```cpp
#include <iostream>
#include "clock.h"

using namespace std;
using namespace susan;
int main(void)
{
    CalendarLite cal(1, 0, 0, 9, 1, 1);//创建一个日期对象(Create a date object)
    CalendarLite cal2(Clock(1,2,3));//将时钟对象转换为日期对象(Convert clock object to date object)
    Clock *clo = &cal;//可以被父类指针引用(Can be referenced by parent class pointer)
    cal.year();//获取年(Get year)
    cal.month();//获取月(Get month)
    cal.day();//获取日(Get day)
    cal.hour();//获取时(Get hour)
    cal.minute();//获取分(Get minute)
    cal.second();//获取秒(Get second)
    cal.reset(12, 34, 56,78,9,10);//重置时间(Reset time)
    cal+=cal2;//日期相加(Add date)
    cal-=cal2;//日期相减(Subtract date)
    cal<cal2;//日期比较(Compare date)
    cal>cal2;//日期比较(Compare date)
    cal<=cal2;//日期比较(Compare date)
    cal>=cal2;//日期比较(Compare date)
    cout<<cal<<endl;//显示日期(Display date)
}
```