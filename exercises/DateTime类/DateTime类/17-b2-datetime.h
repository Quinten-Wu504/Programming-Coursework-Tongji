/* 2154146 吴金轩 计科1班 */
#pragma once

#include "17-b2-date.h"
#include "17-b2-time.h"
#include <climits>

/* 如果有其它全局函数需要声明，写于此处 */
bool check_datetime(int y, int mo, int d, int h, int mi, int s);

/* DateTime类的基本要求：
	1、不允许定义任何数据成员
	2、尽量少定义成员函数
*/

class DateTime :public Date, public Time {
public:
	DateTime();
	DateTime(int y, int mo, int d, int h, int mi, int s);
	DateTime(long long int x);
	DateTime(const DateTime& dt);
	void set(int y = 1900, int mo = 1, int d = 1, int h = 0, int mi = 0, int s = 0);
	void get(int& y, int& mo, int& d, int& h, int& mi, int& s);
	void show();
	operator long long int();
	DateTime& operator++();
	DateTime operator++(int);
	DateTime& operator--();
	DateTime operator--(int);
	friend ostream& operator<<(ostream& out, const DateTime& dt);
	friend istream& operator>>(istream& in, DateTime& dt);
	friend DateTime operator+(DateTime& dt, const long long int seconds);
	friend DateTime operator+(DateTime& dt, const int seconds);
	friend DateTime operator+(const long long int seconds, DateTime& dt);
	friend DateTime operator+(const int seconds, DateTime& dt);
	friend DateTime operator-(const DateTime& dt, const long long int seconds);
	friend DateTime operator-(const DateTime& dt, const int seconds);
	friend long long int operator-(const DateTime& dt1, const DateTime& dt2);
	friend bool operator<(const DateTime& dt1, const DateTime& dt2);
	friend bool operator<=(const DateTime& dt1, const DateTime& dt2);
	friend bool operator>(const DateTime& dt1, const DateTime& dt2);
	friend bool operator>=(const DateTime& dt1, const DateTime& dt2);
	friend bool operator==(const DateTime& dt1, const DateTime& dt2);
	friend bool operator!=(const DateTime& dt1, const DateTime& dt2);

#if defined(__linux) || defined(__linux__)
	friend DateTime operator+(DateTime& dt, const long int seconds);
	friend DateTime operator+(const long int seconds, DateTime& dt);
	friend DateTime operator-(const DateTime& dt, const long int seconds);
#endif // __linux__

};
