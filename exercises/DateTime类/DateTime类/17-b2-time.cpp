/* 2154146 吴金轩 计科1班 */
#include <iostream>
#include <iomanip>
#include "17-b2-time.h"
using namespace std;

/* --- 给出Time类的成员函数的体外实现(含友元及其它必要的公共函数)  --- */
bool check_time(int h, int m, int s)
{
    if (h < 0 || h > 23 || m < 0 || m > 59 || s < 0 || s > 59)
        return 0;
    else
        return 1;
}

/*  Date 类的所有成员函数的体外实现 */
Time::Time()
{
    hour = 0;
    minute = 0;
    second = 0;
}

Time::Time(int h, int m, int s)
{
    if (check_time(h, m, s))
    {
        hour = h;
        minute = m;
        second = s;
    }
    else
    {
        hour = 0;
        minute = 0;
        second = 0;
    }
}

Time::Time(int num_of_sec)
{
    if (num_of_sec < 0) {
        num_of_sec %= 24 * 60 * 60;
        num_of_sec += 24 * 60 * 60;
    }
    else if (num_of_sec > (int)Time(23, 59, 59)) {
        num_of_sec %= 24 * 60 * 60;
    }

    hour = 0;
    minute = 0;
    second = 0;
    for (int i = 0; i < num_of_sec; i++) {
        if (second < 59)
            second++;
        else 
        {
            second = 0;
            if (minute < 59)
                minute++;
            else {
                minute = 0;
                if (hour < 23)
                    hour++;
                else
                    hour = 0;
            }
        }
    }
}

Time::Time(const Time& t)
{
    hour = t.hour;
    minute = t.minute;
    second = t.second;
}

Time::operator int()
{
    int sum_sec = 0;

    for (int i = 0; i < minute; i++)
        sum_sec += 60;
    sum_sec = sum_sec + second;

    for (int temp_hour = 0; temp_hour < hour; temp_hour++) {
        sum_sec += 3600;
    }

    return sum_sec;
}

void Time::set(int h, int m, int s)
{
    if (check_time(h, m, s))
    {
        hour = h;
        minute = m;
        second = s;
    }
    else
    {
        hour = 0;
        minute = 0;
        second = 0;
    }
}

void Time::get(int& h, int& m, int& s)
{
    h = hour;
    m = minute;
    s = second;
}

void Time::show()
{
    cout << *this << endl;
}

Time& Time::operator++()
{
    *this = (int)(*this) + 1;

    return *this;
}

Time Time::operator++(int)
{
    Time t1(*this);

    *this = (int)(*this) + 1;

    return t1;
}

Time& Time::operator--()
{
    *this = (int)(*this) - 1;

    return *this;
}

Time Time::operator--(int)
{
    Time t1(*this);

    *this = (int)(*this) - 1;

    return t1;
}

ostream& operator<<(ostream& out, const Time& t)
{
    out << setfill('0');
    out << setw(2) << t.hour << ":" << setw(2) << t.minute << ":" << setw(2) << t.second;
    out << setfill(' ');
    return out;
}

istream& operator>>(istream& in, Time& t)
{
    int h1 = 0, m1 = 0, s1 = 0;
    in >> h1 >> m1 >> s1;
    t.set(h1, m1, s1);
    return in;
}

Time operator+(Time& t, const int num_of_sec)
{
    int sum = num_of_sec + (int)t;

    return Time(sum);
}

Time operator+(const int num_of_sec, Time& t)
{
    int sum = num_of_sec + (int)t;

    return Time(sum);
}

Time operator-(const Time& t, const int num_of_sec)
{
    Time temp(t);

    temp = (int)temp - num_of_sec;

    return temp;
}

int operator-(const Time& t1, const Time& t2)
{
    Time temp1(t1), temp2(t2);
    return ((int)temp1 - (int)temp2);
}

bool operator<(const Time& t1, const Time& t2)
{
    Time temp1(t1), temp2(t2);
    return ((int)(temp1) < (int)(temp2));
}

bool operator<=(const Time& t1, const Time& t2)
{
    Time temp1(t1), temp2(t2);
    return ((int)(temp1) <= (int)(temp2));
}

bool operator>(const Time& t1, const Time& t2)
{
    Time temp1(t1), temp2(t2);
    return ((int)(temp1) > (int)(temp2));
}

bool operator>=(const Time& t1, const Time& t2)
{
    Time temp1(t1), temp2(t2);
    return ((int)(temp1) >= (int)(temp2));
}

bool operator==(const Time& t1, const Time& t2)
{
    Time temp1(t1), temp2(t2);
    return ((int)(temp1) == (int)(temp2));
}

bool operator!=(const Time& t1, const Time& t2)
{
    Time temp1(t1), temp2(t2);
    return ((int)(temp1) != (int)(temp2));
}
