#ifndef CLOCK_H_
#define CLOCK_H_
#include<iostream>

namespace susan{

using namespace std;
typedef int clock_t;//Clock类的成员变量的类型
#define myDebug true//测试阶段为真，实际投入使用时需要改为false

/*Clock类
  可以以时分秒显示时间
  可以进行时间的加减运算
*/
class Clock{
private:
    /* 在类声明中初始化静态成员变量必须是常量 */
    /* 因为静态成员属于类本身而不属于某一个特定的对象，
       如果有一个对象A更改了静态成员，那么另一个对象B中的此成员也会改变。
       这是不宜察觉且危险的操作。*/
    static const int clock_base = 60;//时间进制：60
    
    clock_t h_;//时
    clock_t m_;//分
    clock_t s_;//秒

public:
    /*
        特殊成员函数
        以下特殊成员函数如果没有自定义，那么编译器将生产默认函数
        - 构造函数
        - 析构函数
        - 复制构造函数：新建一个对象并将其初始化为同类现有对象时调用
                      默认的复制构造函数只是浅显地复制每一个成员变量的值。
                      如果成员变量是一个指针的话，将会出现复制了指针地址，
                      却释放了指针内存，导致数据损坏的情况。
                      成员变量是一个指针的话，应当自定义一个复制构造函数，
                      来深入地复制指针指向的数据，而非指针本身。
        - 赋值运算符：同复制构造函数，如果成员变量是一个指针的话，
                    一定要自定义一个复制运算符重载函数，
                    来深入地传递指针指向的数据，而非指针本身。
        - 地址运算符

        C++11新特性：
        - 移动构造函数
        - 移动赋值函数
    */
    Clock(){}

    /*如果要在派生类中重新定义基类的方法，
    通常应将基类方法声明为虚的，
    这样程序根据对象类型而不是引用或指针类型来选择饭方法版本。
    为基类声明一个虚析构函数也是一种惯例。*/
    virtual ~Clock(){
        if (myDebug)
            cout<<"Clock的析构函数被调用了\n";
    }
    Clock(clock_t h,clock_t m,clock_t s);//构造函数
    //一个参数的构造函数可以作为转换函数将clock_t值转换为clock类，转换过程可隐式进行
    //使用explicit可以禁用隐式类型转换，只允许显式类型转换
    explicit Clock(clock_t s);//构造函数：将秒数转换为时分秒
    //返回时分秒
    //定义在类内部的函数被隐式地转换为内联函数
    clock_t hour(void)const{return h_;}
    clock_t minute(void)const{return m_;}
    clock_t second(void)const{return s_;}
    
    void reset(clock_t h,clock_t m,clock_t s);//重置时间
    //类的成员函数可以直接访问作为其参数的同类型对象的私有成员
    const Clock operator+(const Clock& clk)const;
    //两个时钟相加相减不应该更改两个时钟的数值，所以应该新建对象获取两者之和并返回
    //正如两个int值相加是个常量，两个时钟相加也应该是个常量，所以应该返回const对象
    const Clock operator-(const Clock& clk)const;
    
    void operator+=(const Clock& clk){*this = *this + clk;}
    void operator-=(const Clock& clk){*this = *this - clk;}

    //仅提供时钟与时钟之间的大小比较，我不认为时钟与一个常数比较大小有什么意义
    //如果需要将秒数与时钟比较，那么应该将秒数转化为时钟后再比较
    bool operator<(const Clock& clk)const{return clock_t(*this)<clock_t(clk);}
    bool operator>(const Clock& clk)const{return clock_t(*this)>clock_t(clk);}
    bool operator<=(const Clock& clk)const{return clock_t(*this)<=clock_t(clk);}
    bool operator>=(const Clock& clk)const{return clock_t(*this)>=clock_t(clk);}

    //C++11中，explicit同样可以用于转换函数，explicit只需要置于声明前，定义处不需要
    //Clock转换为clock_t的函数，可隐式调用(P.S.不能对转换函数定义返回值类型)
    //强制类型转换，将Clock类强制转换为clock_t
    explicit operator clock_t()const{return h_*clock_base*clock_base+m_*clock_base+s_;}
    //友元函数与该类的成员函数具有相同的访问权限
    friend ostream& operator<<(ostream& os,const Clock& clk);

    /*静态成员函数
      声明方式，正常函数声明前加上关键字static
      与静态成员变量相对的也存在静态成员函数，不与类对象相关联，只能用类名和作用与解析运算符调用（非常合理）
      静态成员函数不能通过对象调用，也不能使用this指针，也不能使用非静态数据成员
    */
    static const int CLOCK_BASE(void){return clock_base;}

    //不使用virtual关键字：程序将根据引用类型或指针类型选择方法
    //使用virtual关键字：程序将根据引用或指针指向的对象的类型来选择方法
    virtual void virtual_test(void)const{cout<< "Clock的虚方法被调用了\n";}
};

Clock::Clock(clock_t h,clock_t m,clock_t s){
    s_=s%clock_base;
    m_=m%clock_base+s/clock_base;
    h_=h+m/clock_base;
}

Clock::Clock(clock_t s){
    s_=s%clock_base;//获取秒余数
    m_=s/clock_base;//获取总分钟数
    h_=m_/clock_base;//获取小时数
    m_=m_%clock_base;//获取分钟余数
}

void Clock::reset(clock_t h,clock_t m,clock_t s){
    s_=s%clock_base;
    m_=m%clock_base+s/clock_base;
    h_=h+m/clock_base;
}

const Clock Clock::operator+(const Clock& clk)const{
    Clock r(h_+clk.h_,m_+clk.m_,s_+clk.s_);
    r.m_+=r.s_/clock_base;
    r.s_%=clock_base;
    r.h_+=r.m_/clock_base;
    r.m_%=clock_base;
    return r;//返回函数内的局部变量时不能使用引用
}

const Clock Clock::operator-(const Clock& clk)const{
    Clock r;
    clock_t iSec = h_*clock_base*clock_base+m_*clock_base+s_;
    clock_t iClkSec = clk.h_*clock_base*clock_base+clk.m_*clock_base+clk.s_;
    clock_t s,m,h;
    iSec-=iClkSec;
    s=iSec%clock_base;
    m=iSec/clock_base;
    h=m/clock_base;
    m=m%clock_base;
    r.reset(h,m,s);
    
    return r;
}

//友元函数定义中不下需要使用关键字friend
ostream& operator<<(ostream& os,const Clock& clk){

    if(clk.h_ < 0||clk.m_<0||clk.s_<0){
        //如果时间是负值，那么显示上只在最左侧显示一个负号
        cout<<"-"<<abs(clk.h_)<<":"<<abs(clk.m_)<<":"<<abs(clk.s_);
    }
    else{
        cout<<clk.h_<<":"<<clk.m_<<":"<<clk.s_;
    }
    return os;
}


typedef int64_t calendar_t;//CalendarLite类的成员变量的数据类型
//公有派生的日历类(简化版的)
//公有派生：基类的公有成员将成为派生类的公有成员，
//基类的私有成员可通过积累的公有（保护）方法访问。

//共有派生是一种is-a的关系，即日期是时间就像苹果是水果一样
class CalendarLite: public Clock{
//派生类存储了基类的数据成员
//派生类可以使用基类的方法
private:
    static const int day_base = 24;//每天有24小时
    static const int month_base = 30;//每个月30天实际上每个月30或者31天，甚至2月才
                                     //29天，这里为了使得程序简单，粗略使用30天为单位
    static const int year_base = 12;//每年12个月
    //派生类可以添加额外的数据成员或函数
    //对于日历来说，除了时分秒的显示，还应该显示年月日
    calendar_t year_;//年
    calendar_t month_;//月
    calendar_t day_;//日

public:
    CalendarLite(){}
    ~CalendarLite(){
        if (myDebug)
            cout<<"CalendarLite的析构函数被调用了\n";
    }//派生类过期时，先调用派生类的析构函数，再调用基类的析构函数

    //派生类需要自己的构造函数
    //创建派生类对象前，程序先创建基类对象
    CalendarLite(calendar_t year,calendar_t month,calendar_t day,
        clock_t hour,clock_t minute,clock_t second);
    CalendarLite(calendar_t second);
    //允许使用时钟类构造日期类，但是需要显示调用构造函数。
    explicit CalendarLite(const Clock& clo):
        Clock(clo.hour(),clo.minute(),clo.second()),
        year_(0),month_(0),day_(0){}

    calendar_t year(void)const{return year_;}
    calendar_t month(void)const{return month_;}
    calendar_t day(void)const{return day_;}

    //派生类重载了基类的reset函数，但是使用virtual关键字是无效的，因为两个reset函数
    //的参数数量不一样，派生类调用reset函数就是调用自己的，
    //基类指针或者引用了派生类，然后调用reset函数，即使使用了virtual关键字，
    //也只能调用基类的reset函数，若调用派生类的将会报错。
    //虽然同名为reset,但是参数数量不一样，可能被编译器视为了两个不同的函数，但是又由于
    //与基类reset同名，所以派生类是无法调用基类的reset函数的。
    /*重新定义了与基类同名但是函数特征（参数）不同的话，基类同名函数将会被隐藏，无法调用*/
    /*
      对于这个reset函数，理论上我应当让它与基类的参数完全一样，
      要是完全一样的话，功能又无法实现...
      待定...
    */
    void reset(calendar_t year,calendar_t month,calendar_t day,
        clock_t hour,clock_t minute,clock_t second);

    const CalendarLite operator+(const CalendarLite& clk)const;
    const CalendarLite operator-(const CalendarLite& clk)const;

    void operator+=(const CalendarLite& clk){*this = *this + clk;}
    void operator-=(const CalendarLite& clk){*this = *this - clk;}

    //将日期强制转换为秒
    explicit operator calendar_t(void)const;
    //日期比较函数
    bool operator<(const CalendarLite& clk)const{return calendar_t(*this)<calendar_t(clk);}
    bool operator>(const CalendarLite& clk)const{return calendar_t(*this)>calendar_t(clk);}
    bool operator<=(const CalendarLite& clk)const{return calendar_t(*this)<=calendar_t(clk);}
    bool operator>=(const CalendarLite& clk)const{return calendar_t(*this)>=calendar_t(clk);}

    //友元函数函数不能定义为虚函数，因为友元函数无法被继承
    //无法被继承也就谈不上是同一个函数，也不需要虚方法。
    friend ostream& operator<<(ostream& os,const CalendarLite& cal);

    //学习需函数时练习用的，库发布时应当删除此函数
    //虚函数的实现
    /*每个含有虚函数的类都有一个隐藏的虚函数表成员，虚函数表里面存储着类中所有虚函数的地址
      派生类虚函数表内的函数地址是派生类重载的虚函数地址。当指针或者引用调用虚函数时，将会
      在指向（引用）对象的虚函数表中查找虚函数并调用。*/

    /*需函数注意事项*/
    /*
      1.构造函数不能是虚函数
      2.析构函数应当是虚函数：保证有限释放派生类的内存，再释放基类内存
      3.友元函数不能是需函数：友元函数不是类成员，只有类成员才能是虚函数（trick：让友元函数使用虚函数）
      4.重新定义了与基类同名但是函数特征（参数）不同的话，基类同名函数将会被隐藏，无法调用。
        4-1：所以重新定义继承的基类方法的话，应当保持与原来的原型相同
        4-2：基类的函数本身就已经被重载了几个，那么派生类继承时要将基类重载的所有函数都重新定义一遍
        否则，基类未被派生类重新定义的重载函数将会被隐藏。
    */

    virtual void virtual_test(void)const{cout<<"CalendarLite的虚方法被调用了\n";}
};

CalendarLite::CalendarLite(calendar_t year,calendar_t month,calendar_t day,
    clock_t hour,clock_t minute,clock_t second):Clock(hour,minute,second){
/*派生类构造函数应通过初始化成员列表将基类信息传递给基类的构造函数*/
    year_=year;
    month_=month;
    day_=day;
}

CalendarLite::CalendarLite(calendar_t second):
    Clock((clock_t)(second%(day_base*Clock::CLOCK_BASE()*Clock::CLOCK_BASE()))){
    day_=second/(day_base*Clock::CLOCK_BASE()*Clock::CLOCK_BASE());
    month_=day_/month_base;
    year_=month_/year_base;
    day_=day_-month_*month_base;
    month_=month_-year_*year_base;
    
}

void CalendarLite::reset(calendar_t year,calendar_t month,calendar_t day,
clock_t hour,clock_t minute,clock_t second){
    year_=year;
    month_=month;
    day_=day;
    Clock::reset(hour,minute,second);//调用基类的reset方法
}

//日期类与时钟类相加时
const CalendarLite CalendarLite::operator+(const CalendarLite& clk)const{
    //先将时分秒相加
    Clock clotemp(hour()+clk.hour(),minute()+clk.minute(),second()+clk.second());
    //再构建一个日期类：这个日期类已经将时分秒完美地相加了，只需要处理年月日即可
    CalendarLite r(year_+clk.year_,month_+clk.month_,day_+clk.day_+clotemp.hour()/day_base,
    clotemp.hour()%day_base,clotemp.minute(),clotemp.second());

    r.month_+=r.day_/month_base;
    r.day_=r.day_%month_base;
    r.year_+=r.month_/year_base;
    r.month_=r.month_%year_base;
    
    return r;
}

const CalendarLite CalendarLite::operator-(const CalendarLite& clk)const{
    //首先将时分秒的时间相减
    Clock clotemp = (Clock)*this-(Clock)clk;

    //获取日期的差值
    calendar_t alldays = (day_+month_*month_base+year_*year_base*month_base)-
        (clk.day()+clk.month()*month_base+clk.year()*year_base*month_base);
    calendar_t y,m,d;
    d=alldays%month_base;//获取天数
    m=alldays/month_base;//获取总共的月数
    y=m/year_base;//获取年数
    m=m%year_base;//获取取年后的月数
    CalendarLite r(y,m,d,clotemp.hour(),clotemp.minute(),clotemp.second());

    return r;
}

CalendarLite::operator calendar_t(void)const{
    return ((day_+month_*month_base+year_*year_base*month_base)*day_base
    + hour())*CLOCK_BASE()*CLOCK_BASE()+minute()*CLOCK_BASE()+second();
}

ostream& operator<<(ostream& os,const CalendarLite& cal){
    //我不知道一个负数的日期有什么意义，
    //既然日期的减法运算可以获得负数，那么就姑且允许它显示负数日期
    if(cal.year_ < 0||cal.month_<0||cal.day_<0||
        cal.hour()<0||cal.minute()<0||cal.second()<0){
        //显示负数日期时，将负号置于最左侧
        os<<"-"<<abs(cal.year_)<<"年"<<abs(cal.month_)<<"月"<<abs(cal.day_)<<"日 "
        <<abs(cal.hour())<<":"<<abs(cal.minute())<<":"<<abs(cal.second());
    }
    else{
        os<<cal.year_<<"年"<<cal.month_<<"月"<<cal.day_<<"日 "
        <<cal.hour()<<":"<<cal.minute()<<":"<<cal.second();
    }
    return os;
}

}
#endif