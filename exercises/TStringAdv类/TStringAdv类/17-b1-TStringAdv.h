/* 2154146 吴金轩 计科1班 */

#pragma once

#include <iostream>
#include <climits>
#include "17-b1-TString.h"
using namespace std;

class TStringAdv : public TString {
public:
	// 构造函数
	TStringAdv();
	TStringAdv(const int n, bool not_construct);
	TStringAdv(const char* s);
	TStringAdv(const TString& s_copy);

	TStringAdv& assign(const TStringAdv& ts2);
	TStringAdv& assign(const char *s);

	TStringAdv& append(const TStringAdv& ts2);
	TStringAdv& append(const char* s);
	TStringAdv& append(const char& c);

	TStringAdv& insert(const TStringAdv& ts2, int pos);
	TStringAdv& insert(const char* s, int pos);
	TStringAdv& insert(const char& c, int pos);


	TStringAdv& erase(const TStringAdv& ts2);
	TStringAdv& erase(const char* s);
	TStringAdv& erase(const char& c);

	TStringAdv substr(const int pos, const int len = INT_MAX) const;

	char& at(const int n) const;
};

int TStringAdvLen(const TStringAdv& s);