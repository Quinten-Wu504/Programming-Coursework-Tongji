/* 2154146 吴金轩 计科1班 */
#include <iostream>
#include <iomanip>
#include "17-b2-date.h"
using namespace std;

/*  Date 类的所有成员函数的体外实现 */
Date::Date()
{
    year = 1900;
    month = 1;
    day = 1;
}

Date::Date(int y, int m, int d)
{
    if (check_date(y, m, d))
    {
        year = y;
        month = m;
        day = d;
    }
    else
    {
        year = 1900;
        month = 1;
        day = 1;
    }
}

Date::Date(int num_of_day)
{
    if (num_of_day < 0) {
        num_of_day %= (int)Date(2099, 12, 31) + 1;
        num_of_day += (int)Date(2099, 12, 31) + 1;
    }
    else if (num_of_day > (int)Date(2099,12,31)) {
        num_of_day %= (int)Date(2099, 12, 31) + 1;
    }

    year = 1900;
    month = 1;
    day = 1;
    for (int i = 0; i < num_of_day; i++) {
        if (month != 2) {
            if (day < month_days[month - 1]) {
                day++;
            }
            else {
                day = 1;
                if (month < 12) {
                    month++;
                }
                else {
                    month = 1;
                    year++;
                }
            }
        }
        else {
            if (day < month_days[2 - 1] + leap_year_determing(year)) {
                day++;
            }
            else {
                day = 1;
                if (month < 12) {
                    month++;
                }
                else {
                    month = 1;
                    year++;
                }
            }
        }
    }
}

Date::Date(const Date& d)
{
    year = d.year;
    month = d.month;
    day = d.day;
}

Date::operator int()
{
    int sum_day = 0;

    for (int i = 0; i < (month - 1); i++) {
        if (i != 1)
            sum_day += month_days[i];
        else
            sum_day += month_days[i] + leap_year_determing(year);
    }
    sum_day = sum_day + day;

    for (int temp_year = 1900; temp_year < year; temp_year++) {
        sum_day += 365 + leap_year_determing(temp_year);
    }

    return sum_day - 1;
}

void Date::set(int y, int m, int d)
{
    if (check_date(y, m, d))
    {
        year = y;
        month = m;
        day = d;
    }
    else
    {
        year = 1900;
        month = 1;
        day = 1;
    }
}

void Date::get(int& y, int& m, int& d)
{
    y = year;
    m = month;
    d = day;
}

void Date::show()
{
    cout << *this << endl;
}

Date& Date::operator++()
{
    *this = (int)(*this) + 1;

    return *this;
}

Date Date::operator++(int)
{
    Date d1(*this);

    *this = (int)(*this) + 1;

    return d1;
}

Date& Date::operator--()
{
    *this = (int)(*this) - 1;

    return *this;
}

Date Date::operator--(int)
{
    Date d1(*this);

    *this = (int)(*this) - 1;

    return d1;
}

ostream& operator<<(ostream& out, const Date& d)
{
    out << setfill('0');
    out << d.year << "-" << setw(2) << d.month << "-" << setw(2) << d.day;
    return out;
}

istream& operator>>(istream& in, Date& d)
{
    int y1 = 0, m1 = 0, d1 = 0;
    in >> y1 >> m1 >> d1;
    d.set(y1, m1, d1);
    return in;
}

Date operator+(Date& d, const int num_of_day)
{
    int sum = num_of_day + (int)d;

    return Date(sum);
}

Date operator+(const int num_of_day, Date& d)
{
    int sum = num_of_day + (int)d;

    return Date(sum);
}

Date operator-(const Date& d, const int num_of_day)
{
    Date temp(d);

    temp = (int)temp-num_of_day;

    return temp;
}

int operator-(const Date& d1, const Date& d2)
{
    Date temp1(d1), temp2(d2);
    return ((int)temp1-(int)temp2);
}

bool operator<(const Date& d1, const Date& d2)
{
    Date temp1(d1), temp2(d2);
    return ((int)(temp1) < (int)(temp2));
}

bool operator<=(const Date& d1, const Date& d2)
{
    Date temp1(d1), temp2(d2);
    return ((int)(temp1) <= (int)(temp2));
}

bool operator>(const Date& d1, const Date& d2)
{
    Date temp1(d1), temp2(d2);
    return ((int)(temp1) > (int)(temp2));
}

bool operator>=(const Date& d1, const Date& d2)
{
    Date temp1(d1), temp2(d2);
    return ((int)(temp1) >= (int)(temp2));
}

bool operator==(const Date& d1, const Date& d2)
{
    Date temp1(d1), temp2(d2);
    return ((int)(temp1) == (int)(temp2));
}

bool operator!=(const Date& d1, const Date& d2)
{
    Date temp1(d1), temp2(d2);
    return ((int)(temp1) != (int)(temp2));
}

/* 其它全局函数的实现 */
int leap_year_determing(int year)
{
    if ((!(year % 4) && year % 100) || !(year % 400))
        return 1;
    else
        return 0;
}

bool check_date(int y, int m, int d)
{
    if (y < 1900 || y > 2099 || m < 1 || m > 12)
        return 0;
    else
    {
        if (m == 2) {
            if (d >= 1 && d <= month_days[2 - 1] + leap_year_determing(y))
                return 1;
            else
                return 0 ;
        }
        else {
            if (d >= 1 && d <= month_days[m - 1])
                return 1;
            else
                return 0;
        }
    }
}