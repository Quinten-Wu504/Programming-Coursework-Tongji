/* 2154146 Îâ½ðÐù ¼Æ¿Æ */
#pragma once
#include <string>
#include <fstream>
using namespace std;

int strlen_str(string str);
int strcmp_str(const string str1, const string str2);
int strcmp_str(const string str1, const string str2, const bool ignore_lower_upper_case);

int hex_to_num(char hex_num);
int char_to_int(const char arr[], int size);
int hex_str_to_dec_num(const char* str, int length);
string int_to_str(const int& num);
void print_hex_number(unsigned int dec_num, int num_of_digit);

string trim_blank(string line_str, bool right, bool left);
void trim_blank(char** p_line_str, bool right, bool left);
void print_hex_line(string str, bool eof);

void intercept_file_path(char* procname, const char* file_path);

string get_file_n_line(ifstream& infile, int n);

bool is_UTF8(const string& line_text);
bool is_PDF(const string& line_text);
bool check_comment(const string& line_text);
int check_comment_item_num(const string& line_text);
string get_filetype(const string& filename);