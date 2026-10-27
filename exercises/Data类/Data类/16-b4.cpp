/* 2154146 吴金轩 计科1班 */
#include <iostream>
#include "16-b4.h"
using namespace std;

/* 给出 Date 类的所有成员函数的体外实现 */
Date::Date()
{
    year = 2000;
    month = 1;
    day = 1;
}

Date::Date(int y, int m, int d)
{
    if (y >= 1900 && y <= 2099)
        year = y;
    else
        year = 2000;

    if (m >= 1 && m <= 12)
        month = m;
    else
        month = 1;

    if (month == 2) {
        if (d >= 1 && d <= month_days[2 - 1] + leap_year_determing(year))
            day = d;
        else
            day = 1;
    }
    else {
        if (d >= 1 && d <= month_days[month - 1])
            day = d;
        else
            day = 1;
    }
}

Date::Date(int num_of_day)
{
    if (num_of_day <= 1) {
        year = 1900;
        month = 1;
        day = 1;
    }
    else if (num_of_day >= 73049) {
        year = 2099;
        month = 12;
        day = 31;
    }
    else {
        year = 1900;
        month = 1;
        day = 0;
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

    return sum_day;
}

void Date::set(int y, int m, int d)
{
    if (y >= 1900 && y <= 2099)
        year = y;
    else if (y != 0)
        year = 2000;
    else
        year = year;

    if (m >= 1 && m <= 12)
        month = m;
    else if (m != 0)
        month = 1;
    else
        month = month;

    if (month == 2) {
        if (d >= 1 && d <= month_days[2 - 1] + leap_year_determing(year))
            day = d;
        else if (d != 0)
            day = 1;
        else {
            if (day >= 1 && day <= month_days[2 - 1] + leap_year_determing(year))
                day = day;
            else
                day = 1;
        }
    }
    else {
        if (d >= 1 && d <= month_days[month - 1])
            day = d;
        else if (d != 0)
            day = 1;
        else {
            if (day >= 1 && day <= month_days[month - 1])
                day = day;
            else
                day = 1;
        }
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
    cout << year << "年" << month << "月" << day << "日" << endl;
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
    out << d.year << "年" << d.month << "月" << d.day << "日";
    return out;
}

istream& operator>>(istream& in, Date& d)
{
    int y1 = 0, m1 = 0, d1 = 0;
    in >> y1 >> m1 >> d1;
    d.set(y1, m1, d1);
    return in;
}

Date operator+(const Date& d, const int num_of_day)
{
    Date temp(d);

    for (int i = 0; i < num_of_day; i++) {
        if (temp.year == 2099 && temp.month == 12 && temp.day == 31)
            break;

        if (temp.month != 2) {
            if (temp.day < month_days[temp.month - 1]) {
                temp.day++;
            }
            else {
                temp.day = 1;
                if (temp.month < 12) {
                    temp.month++;
                }
                else {
                    temp.month = 1;
                    temp.year++;
                }
            }
        }
        else {
            if (temp.day < month_days[2 - 1] + leap_year_determing(temp.year)) {
                temp.day++;
            }
            else {
                temp.day = 1;
                if (temp.month < 12) {
                    temp.month++;
                }
                else {
                    temp.month = 1;
                    temp.year++;
                }
            }
        }
    }

    return temp;
}

Date operator+(const int num_of_day, const Date& d)
{
    Date temp(d);

    for (int i = 0; i < num_of_day; i++) {
        if (temp.year == 2099 && temp.month == 12 && temp.day == 31)
            break;

        if (temp.month != 2) {
            if (temp.day < month_days[temp.month - 1]) {
                temp.day++;
            }
            else {
                temp.day = 1;
                if (temp.month < 12) {
                    temp.month++;
                }
                else {
                    temp.month = 1;
                    temp.year++;
                }
            }
        }
        else {
            if (temp.day < month_days[2 - 1] + leap_year_determing(temp.year)) {
                temp.day++;
            }
            else {
                temp.day = 1;
                if (temp.month < 12) {
                    temp.month++;
                }
                else {
                    temp.month = 1;
                    temp.year++;
                }
            }
        }
    }

    return temp;
}

Date operator-(const Date& d, const int num_of_day)
{
    Date temp(d);

    temp = (int)(temp)-num_of_day;

    return temp;
}

int operator-(const Date& d1, const Date& d2)
{
    Date temp1(d1), temp2(d2);
    return ((int)(temp1) - (int)(temp2));
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

/* 如果有需要的其它全局函数的实现，可以写于此处 */
int leap_year_determing(int year)
{
    if ((!(year % 4) && year % 100) || !(year % 400))
        return 1;
    else
        return 0;
}