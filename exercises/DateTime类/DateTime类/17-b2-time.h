/* 2154146 吴金轩 计科1班 */
#pragma once

#include <iostream>
using namespace std;

/* 如果有其它全局函数需要声明，写于此处 */
bool check_time(int h, int m, int s);

/* Time类的声明 */
class Time {
protected:
	/* 除这三个以外，不允许再定义任何数据成员 */
	int hour;
	int minute;
	int second;
public:
	Time();
	Time(int h, int m, int s);
	Time(int x);
	Time(const Time& t);
	void set(int h, int m = 0, int s = 0);
	void get(int& h, int& m, int& s);
	void show();
	operator int();
	Time& operator++();
	Time operator++(int);
	Time& operator--();
	Time operator--(int);
	friend ostream& operator<<(ostream& out, const Time& t);
	friend istream& operator>>(istream& in, Time& t);
	friend Time operator+(Time& t, const int seconds);
	friend Time operator+(const int days, Time& t);
	friend Time operator-(const Time& t, const int seconds);
	friend int operator-(const Time& t1, const Time& t2);
	friend bool operator<(const Time& t1, const Time& t2);
	friend bool operator<=(const Time& d1, const Time& d2);
	friend bool operator>(const Time& d1, const Time& d2);
	friend bool operator>=(const Time& d1, const Time& d2);
	friend bool operator==(const Time& d1, const Time& d2);
	friend bool operator!=(const Time& d1, const Time& d2);
};
