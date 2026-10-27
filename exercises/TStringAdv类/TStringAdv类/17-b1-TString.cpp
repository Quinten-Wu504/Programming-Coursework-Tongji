/* 2154146 吴金轩 计科1班 */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "17-b1-TString.h"
using namespace std;

// 构造函数
TString::TString()
{
	len = 0;
	content = new(nothrow) char[1];
	if (content == NULL) {
		cout << "No Memory!" << endl;
		return;
	}
	content[0] = '\0';
}

TString::TString(const int n, bool not_construct)
{
	len = n;
	content = new(nothrow) char[len + 1];
	if (content == NULL) {
		cout << "No Memory!" << endl;
		return;
	}
	content[0] = '\0';
}

TString::TString(const char* s)
{
	if (s == NULL)
		len = 0;
	else
		len = strlen(s);

	content = new(nothrow) char[len + 1];
	if (content == NULL) {
		cout << "No Memory!" << endl;
		return;
	}

	if (len != 0)
		memcpy(content, s, len + 1);
	else
		content[0] = '\0';
}

TString::TString(const TString& s_copy)
{
	len = s_copy.len;
	content = new(nothrow) char[len + 1];
	if (content == NULL) {
		cout << "No Memory!" << endl;
		return;
	}
	content[0] = '\0';
	memcpy(content, s_copy.content, len + 1);
}



// 析构函数
TString::~TString()
{
	if (content != NULL)
		delete[]content;
}



// 取类数据成员
const char* TString::c_str() const
{
	return content;
}

int TString::length() const
{
	return len;
}



// set函数
void TString::set(const char* s)
{
	if (s == NULL) {
		char* temp = new(nothrow) char[1];
		if (temp == NULL)
			return;
		temp[0] = '\0';
		delete[]content;
		content = temp;
		len = 0;
	}
	else {
		char* temp = new(nothrow) char[strlen(s) + 1];
		if (temp == NULL)
			return;
		temp[0] = '\0';
		memcpy(temp, s, strlen(s) + 1);
		delete[]content;
		content = temp;
		len = strlen(s);
	}
}

void TString::set(const TString& s)
{
	len = s.len;
	char* temp = new(nothrow) char[s.len + 1];
	if (temp == NULL)
		return;
	temp[0] = '\0';
	memcpy(temp, s.content, len + 1);

	delete[]content;

	content = temp;
}



// +运算符的重载友元函数
TString operator+(const TString& s1, const char s2)
{
	TString s3(s1.len + 1, 1);
	if (s3.content == NULL) {
		return s1;
	}

	memcpy(s3.content, s1.content, s1.len + 1);
	s3.content[s1.len] = s2;
	s3.content[s1.len + 1] = '\0';

	return s3;
}

TString operator+(const char s1, const TString& s2)
{
	TString s3(s2.len + 1, 1);
	if (s3.content == NULL) {
		return s2;
	}

	s3.content[0] = s1;
	s3.content[1] = '\0';
	strcat(s3.content, s2.content);

	return s3;
}

TString operator+(const TString& s1, const char* s2)
{
	int s2_len = 0;
	if (s2 == NULL)
		s2_len = 0;
	else
		s2_len = strlen(s2);

	TString s3(s1.len + s2_len, 1);
	if (s3.content == NULL) {
		return s1;
	}
	memcpy(s3.content, s1.content, s1.len + 1);
	if (s2_len != 0)
		strcat(s3.content, s2);

	return s3;
}

TString operator+(const char* s1, const TString& s2)
{
	int s1_len = 0;
	if (s1 == NULL)
		s1_len = 0;
	else
		s1_len = strlen(s1);

	TString s3(s1_len + s2.len, 1);
	if (s3.content == NULL) {
		return s2;
	}

	if (s1_len != 0)
		memcpy(s3.content, s1, strlen(s1) + 1);
	strcat(s3.content, s2.content);

	return s3;
}

TString operator+(const TString& s1, const TString& s2)
{
	TString s3(s1.len + s2.len, 1);
	if (s3.content == NULL) {
		return s1;
	}

	memcpy(s3.content, s1.content, s1.len + 1);
	strcat(s3.content, s2.content);

	return s3;
}



// -运算符的重载友元函数
TString operator-(const TString& s1, const char s2)
{
	const char* s2_loc = strchr(s1.content, s2);

	if (s2_loc == NULL) {
		return s1;
	}
	else {
		TString s3;
		int loc = (int)(s2_loc - s1.content);

		char* temp = new(nothrow) char[s1.len];
		if (temp == NULL) {
			cout << "No Memory!" << endl;
			return s3;
		}

		for (int i = 0; i < s1.len + 1; i++) {
			if (i < loc)
				temp[i] = s1.content[i];
			else if (i >= loc + 1)
				temp[i - 1] = s1.content[i];
		}

		s3.set(temp);

		delete[]temp;

		return s3;
	}
}

TString operator-(const TString& s1, const char* s2)
{
	if (s2 != NULL) {
		const char* s2_loc = strstr(s1.content, s2);

		if (s2_loc == NULL)
			return s1;
		else {
			TString s3;
			int loc = (int)(s2_loc - s1.content);
			int s2_len = strlen(s2);

			char* temp = new(nothrow) char[s1.len - s2_len + 1];
			if (temp == NULL) {
				cout << "No Memory!" << endl;
				return s3;
			}

			for (int i = 0; i < s1.len + 1; i++) {
				if (i < loc)
					temp[i] = s1.content[i];
				else if (i >= loc + s2_len)
					temp[i - s2_len] = s1.content[i];
			}

			s3.set(temp);

			delete[]temp;

			return s3;
		}
	}
	else
		return s1;
}

TString operator-(const TString& s1, const TString& s2)
{
	const char* s2_loc = strstr(s1.content, s2.content);

	if (s2_loc == NULL) {
		return s1;
	}
	else {
		TString s3;
		int loc = (int)(s2_loc - s1.content);

		char* temp = new(nothrow) char[s1.len - s2.len + 1];
		if (temp == NULL) {
			cout << "No Memory!" << endl;
			return s3;
		}

		for (int i = 0; i < s1.len + 1; i++) {
			if (i < loc)
				temp[i] = s1.content[i];
			else if (i >= loc + s2.len)
				temp[i - s2.len] = s1.content[i];
		}

		s3.set(temp);

		delete[]temp;

		return s3;
	}
}



// *运算符的重载友元函数
TString operator*(const TString& s, const int& n)
{
	TString s_temp;
	char* temp = new(nothrow) char[s.len * n + 1];
	if (temp == NULL) {
		cout << "No Memory!" << endl;
		return s_temp;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < s.len; j++) {
			temp[i * s.len + j] = s.content[j];
		}
	}
	temp[s.len * n] = '\0';

	s_temp.set(temp);

	delete[]temp;

	return s_temp;
}



// +=运算符的成员函数重载
TString& TString::operator+=(const char s)
{
	char* temp = new(nothrow) char[this->len + 1 + 1];
	if (temp == NULL) {
		cout << "No Memory!" << endl;
		return *this;
	}

	memcpy(temp, this->content, len + 1);
	temp[this->len] = s;
	temp[this->len + 1] = '\0';

	delete[]this->content;

	this->len += 1;
	this->content = temp;

	return *this;
}

TString& TString::operator+=(const char* s)
{
	if (s != NULL) {
		int len_s = strlen(s);
		char* temp = new(nothrow) char[this->len + len_s + 1];
		if (temp == NULL) {
			cout << "No Memory!" << endl;
			return *this;
		}

		memcpy(temp, this->content, this->len + 1);
		strcat(temp, s);

		delete[]this->content;

		this->len += len_s;
		this->content = temp;

		return *this;
	}
	else
		return *this;
}

TString& TString::operator+=(const TString& s)
{
	char* temp = new(nothrow) char[this->len + s.len + 1];
	if (temp == NULL) {
		cout << "No Memory!" << endl;
		return *this;
	}

	memcpy(temp, this->content, this->len + 1);
	strcat(temp, s.content);

	delete[]this->content;

	this->len += s.len;
	this->content = temp;

	return *this;
}



// -=运算符的成员函数重载
TString& TString::operator-=(const char s)
{
	const char* s_loc = strchr(content, s);

	if (s_loc == NULL)
		return *this;
	else {
		int loc = (int)(s_loc - content);

		char* temp = new(nothrow) char[len];
		if (temp == NULL) {
			cout << "No Memory!" << endl;
			return *this;
		}

		for (int i = 0; i < len + 1; i++) {
			if (i < loc)
				temp[i] = content[i];
			else if (i >= loc + 1)
				temp[i - 1] = content[i];
		}

		this->set(temp);

		delete[]temp;

		return *this;
	}
}

TString& TString::operator-=(const char* s)
{
	if (s != NULL) {
		const char* s_loc = strstr(content, s);

		if (s_loc == NULL)
			return *this;
		else {
			int loc = (int)(s_loc - content);
			int s_len = strlen(s);

			char* temp = new(nothrow) char[len - s_len + 1];
			if (temp == NULL) {
				cout << "No Memory!" << endl;
				return *this;
			}

			for (int i = 0; i < len + 1; i++) {
				if (i < loc)
					temp[i] = content[i];
				else if (i >= loc + s_len)
					temp[i - s_len] = content[i];
			}

			delete[]this->content;

			this->len = this->len - s_len;
			this->content = temp;

			return *this;
		}
	}
	else
		return *this;
}

TString& TString::operator-=(const TString& s)
{
	const char* s_loc = strstr(content, s.content);

	if (s_loc == NULL) {
		return *this;
	}
	else {
		int loc = (int)(s_loc - content);

		char* temp = new(nothrow) char[len - s.len + 1];
		if (temp == NULL) {
			cout << "No Memory!" << endl;
			return *this;
		}

		for (int i = 0; i < len + 1; i++) {
			if (i < loc)
				temp[i] = content[i];
			else if (i >= loc + s.len)
				temp[i - s.len] = content[i];
		}

		delete[]this->content;

		this->len = this->len - s.len;
		this->content = temp;

		return *this;
	}
}



// *=运算符的成员函数重载
TString& TString::operator*=(const int& n)
{
	char* temp = new(nothrow) char[len * n + 1];
	if (temp == NULL) {
		cout << "No Memory!" << endl;
		return *this;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < len; j++) {
			temp[i * len + j] = content[j];
		}
	}
	temp[len * n] = '\0';

	delete[]this->content;

	this->len = this->len * n;
	this->content = temp;

	return *this;
}



// =运算符的成员函数重载
TString& TString::operator=(const TString& s)
{
	this->set(s);
	return *this;
}

TString& TString::operator=(const char* s)
{
	this->set(s);
	return *this;
}



// 流运算符的友元函数重载
ostream& operator<<(ostream& out, const TString& s)
{
	if (s.len == 0)
		out << "<NULL>";
	else
		out << s.content;

	return out;
}

istream& operator>>(istream& in, TString& s)
{
	char temp = 0;
	s.set(NULL);

	while ((temp = getchar()) == 13 || temp == 10 || temp == ' ');

	s += temp;
	while ((temp = getchar()) != 13 && temp != 10 && temp != ' ') {
		s += temp;
	}

	return in;
}



// []运算符的成员函数重载
char& TString::operator[](const int n) const
{
	return content[n];
}



// !运算符（反转字符串）的友元函数重载
TString operator!(const TString& s)
{
	TString s_temp;
	char* temp = new(nothrow) char[s.len + 1];
	if (temp == NULL) {
		cout << "No Memory!" << endl;
		return s_temp;
	}

	for (int i = 0; i < s.len; i++) {
		temp[i] = s.content[s.len - i - 1];
	}
	temp[s.len] = '\0';

	delete[]s_temp.content;

	s_temp.len = s.len;
	s_temp.content = temp;

	return s_temp;
}



// 比较运算符的友元函数重载
bool operator<(const TString& s1, const TString& s2)
{
	bool result = (strcmp(s1.content, s2.content) < 0) ? 1 : 0;
	return result;
}

bool operator<(const TString& s1, const char* s2)
{
	bool result = 0;
	if (s2 != NULL)
		result = (strcmp(s1.content, s2) < 0) ? 1 : 0;
	else
		result = (strcmp(s1.content, "\0") < 0) ? 1 : 0;
	return result;
}

bool operator<=(const TString& s1, const TString& s2)
{
	bool result = (strcmp(s1.content, s2.content) <= 0) ? 1 : 0;
	return result;
}

bool operator<=(const TString& s1, const char* s2)
{
	bool result = 0;
	if (s2 != NULL)
		result = (strcmp(s1.content, s2) <= 0) ? 1 : 0;
	else
		result = (strcmp(s1.content, "\0") <= 0) ? 1 : 0;
	return result;
}

bool operator>(const TString& s1, const TString& s2)
{
	bool result = (strcmp(s1.content, s2.content) > 0) ? 1 : 0;
	return result;
}

bool operator>(const TString& s1, const char* s2)
{
	bool result = 0;
	if (s2 != NULL)
		result = (strcmp(s1.content, s2) > 0) ? 1 : 0;
	else
		result = (strcmp(s1.content, "\0") > 0) ? 1 : 0;
	return result;
}

bool operator>=(const TString& s1, const TString& s2)
{
	bool result = (strcmp(s1.content, s2.content) >= 0) ? 1 : 0;
	return result;
}

bool operator>=(const TString& s1, const char* s2)
{
	bool result = 0;
	if (s2 != NULL)
		result = (strcmp(s1.content, s2) >= 0) ? 1 : 0;
	else
		result = (strcmp(s1.content, "\0") >= 0) ? 1 : 0;
	return result;
}

bool operator==(const TString& s1, const TString& s2)
{
	bool result = (strcmp(s1.content, s2.content) == 0) ? 1 : 0;
	return result;
}

bool operator==(const TString& s1, const char* s2)
{
	bool result = 0;
	if (s2 != NULL)
		result = (strcmp(s1.content, s2) == 0) ? 1 : 0;
	else
		result = (strcmp(s1.content, "\0") == 0) ? 1 : 0;
	return result;
}

bool operator!=(const TString& s1, const TString& s2)
{
	bool result = (strcmp(s1.content, s2.content) != 0) ? 1 : 0;
	return result;
}

bool operator!=(const TString& s1, const char* s2)
{
	bool result = 0;
	if (s2 != NULL)
		result = (strcmp(s1.content, s2) != 0) ? 1 : 0;
	else
		result = (strcmp(s1.content, "\0") != 0) ? 1 : 0;
	return result;
}





/* 如果有需要的其它全局函数的实现，可以写于此处 */
int TStringLen(const TString& s)
{
	return s.length();
}