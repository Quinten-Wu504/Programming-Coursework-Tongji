/* 2154146 Îâ½ðÐù ¼Æ¿Æ1°à */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "17-b1-TStringAdv.h"
using namespace std;

TStringAdv::TStringAdv() : TString()
{
}

TStringAdv::TStringAdv(const int n, bool not_construct) : TString(n, not_construct)
{
}

TStringAdv::TStringAdv(const char* s) : TString(s)
{
}

TStringAdv::TStringAdv(const TString& s_copy) : TString(s_copy)
{
}


TStringAdv& TStringAdv::assign(const TStringAdv& ts2)
{
	this->set(ts2);
	return *this;
}

TStringAdv& TStringAdv::assign(const char* s)
{
	this->set(s);
	return *this;
}



TStringAdv& TStringAdv::append(const TStringAdv& ts2)
{
	char* temp = new(nothrow) char[this->length() + ts2.length() + 1];
	if (temp == NULL)
	{
		cout << "No Memory!" << endl;
		return *this;
	}

	memcpy(temp, this->c_str(), this->length() + 1);
	strcat(temp, ts2.c_str());

	this->assign(temp);

	return *this;
}

TStringAdv& TStringAdv::append(const char* s)
{
	if (s != NULL)
	{
		int len_s = strlen(s);
		char* temp = new(nothrow) char[this->length() + len_s + 1];
		if (temp == NULL)
		{
			cout << "No Memory!" << endl;
			return *this;
		}

		memcpy(temp, this->c_str(), this->length() + 1);
		strcat(temp, s);

		this->assign(temp);

		return *this;
	}
	else
		return *this;
}

TStringAdv& TStringAdv::append(const char& c)
{
	char* temp = new(nothrow) char[this->length() + 1 + 1];
	if (temp == NULL)
	{
		cout << "No Memory!" << endl;
		return *this;
	}

	memcpy(temp, this->c_str(), this->length() + 1);
	temp[this->length()] = c;
	temp[this->length() + 1] = '\0';

	this->assign(temp);

	return *this;
}



TStringAdv& TStringAdv::insert(const TStringAdv& ts2, int pos)
{
	if (pos < 1 || pos > this->length() + 1)
		return *this;
	else
	{
		char* temp = new(nothrow) char[this->length() + ts2.length() + 1];
		if (temp == NULL)
		{
			cout << "No Memory!" << endl;
			return *this;
		}

		for (int i = 0; i < this->length() + ts2.length(); i++)
		{
			if (i < pos - 1)
				temp[i] = this->at(i);
			else if (i >= pos - 1 && i <= pos + ts2.length() - 2)
				temp[i] = ts2.c_str()[i - pos + 1];
			else
				temp[i] = this->at(i - ts2.length());
		}

		temp[this->length() + ts2.length()] = '\0';

		this->assign(temp);

		return *this;
	}
}

TStringAdv& TStringAdv::insert(const char* s, int pos)
{
	if (pos < 1 || pos > this->length() + 1)
		return *this;
	else
	{
		if (s != NULL)
		{
			int len_s = strlen(s);
			char* temp = new(nothrow) char[this->length() + len_s + 1];
			if (temp == NULL)
			{
				cout << "No Memory!" << endl;
				return *this;
			}

			for (int i = 0; i < this->length() + len_s; i++)
			{
				if (i < pos - 1)
					temp[i] = this->at(i);
				else if (i >= pos - 1 && i <= pos + len_s - 2)
					temp[i] = s[i - pos + 1];
				else
					temp[i] = this->at(i - len_s);
			}

			temp[this->length() + len_s] = '\0';

			this->assign(temp);

			return *this;
		}
		else
			return *this;
	}
}

TStringAdv& TStringAdv::insert(const char& c, int pos)
{
	if (pos < 1 || pos > this->length() + 1)
		return *this;
	else
	{
		if (c != '\0')
		{
			char* temp = new(nothrow) char[this->length() + 1 + 1];
			if (temp == NULL)
			{
				cout << "No Memory!" << endl;
				return *this;
			}

			for (int i = 0; i < this->length() + 1; i++)
			{
				if (i < pos - 1)
					temp[i] = this->at(i);
				else if (i == pos - 1)
					temp[i] = c;
				else
					temp[i] = this->at(i - 1);
			}

			temp[this->length() + 1] = '\0';

			this->assign(temp);

			return *this;
		}
		else
		{
			char* temp = new(nothrow) char[pos];
			if (temp == NULL)
			{
				cout << "No Memory!" << endl;
				return *this;
			}

			for (int i = 0; i < pos - 1; i++)
				temp[i] = this->at(i);

			temp[pos - 1] = '\0';

			this->assign(temp);

			return *this;
		}
	}
}



TStringAdv& TStringAdv::erase(const TStringAdv& ts2)
{
	*this -= ts2;

	return *this;
}

TStringAdv& TStringAdv::erase(const char* s)
{
	*this -= s;

	return *this;
}

TStringAdv& TStringAdv::erase(const char& c)
{
	*this -= c;

	return *this;
}

TStringAdv TStringAdv::substr(const int pos, const int len) const
{
	if (pos <= 0 || pos >= this->length() + 1 || len <= 0)
	{
		TStringAdv s;
		return s;
	}
	else if (len == INT_MAX || pos + len - 1 >= this->length())
	{
		TStringAdv s;
		char* temp = new(nothrow) char[this->length() - pos + 1 + 1];
		if (temp == NULL)
		{
			cout << "No Memory!1" << endl;
			return s;
		}

		for (int i = pos - 1; i < this->length() + 1; i++)
			temp[i - pos + 1] = this->at(i);

		s.assign(temp);

		return s;
	}
	else
	{
		TStringAdv s;
		char* temp = new(nothrow) char[len + 1];
		if (temp == NULL)
		{
			cout << "No Memory!2" << endl;
			return s;
		}

		for (int i = pos - 1; i < pos + len - 1; i++)
			temp[i - pos + 1] = this->at(i);

		temp[len] = '\0';

		s.assign(temp);

		return s;
	}
}



char& TStringAdv::at(const int n) const
{
	return (*this)[n];
}



int TStringAdvLen(const TStringAdv& s)
{
	return s.length();
}