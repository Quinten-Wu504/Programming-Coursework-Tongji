/* 2154146 Îâ½ðÐù ¼Æ¿Æ */
#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "class_dbcfg.h"
#include "class_cross_check_list.h"
#include "../include/common_string_process.h"
#include "../include_mariadb_x86/mysql/mysql.h" 
using namespace std;

string get_stulist_command(const string& cno, const string& stunum);
string get_hwlist_command(const string& cno, const int& chapter, const int& week, const string& filename);

string get_hwfile_path(const string& srcrootdir, const string& cno, const string& stuno, const string& filename);

void count_filetype(const string& hwfile_check_result, int& correct_num, int& unsub_num, int& utf_num, int& notpdf_num, int& notcom_num, int& not3item_num, int& wrongformat_num, int& comwrong_num);
int check_stuinfo(const string& line_text, const string& stu_name, const string& stu_no, const string& stu_major, const string& stu_all_major);
string check_hwfile(const string& action, const string& hwfile_path, const string& hwfile_type, const string& stu_name, const string& stu_no, const string& stu_major, const string& stu_all_major);

void print_footer(const int& num, const int& correct_num, const int& unsub_num, const int& utf_num, const int& notpdf_num, const int& notcom_num, const int& not3item_num, int& wrongformat_num, const int& comwrong_num, const char& fill_char, const string& filename);
void print_staresult(const int& stu_num, const int& filesum, const int& correctsum, const int& unsubsum, const int& utfsum, const int& notpdfsum, const int& notcomsum, const int& not3itemsum, const int& wrongformatsum, const int& comwrongsum);

int action_base_firstline_process(const string& action, dbcfg& db_cfg, const string& cno, const string& stunum, const string& filename, const int& chapter, const int& week);

string check_2ndline(const string& hwfile_path, const string& name, const string& number, cross_check_list*& list, const int& nth_stu);
void count_2ndline_type(const string& hwfile_check_result, int& correct_num, int& unsub_num, int& utf_num, int& notcom_num);
void print_2ndline_footer(const int& stu_num, const int& correct_num, const int& unsub_num, const int& utf_num, const int& notcom_num);
void print_cross_check_result(cross_check_list*& cross_list, const int& stu_num);
int action_secondline_process(dbcfg& db_cfg, const string& cno, const string& stunum, const string& filename);