/* 2154146 吴金轩 计科 */
#include "hw_check_action.h"
#include "../include/common_database_tools.h"

string get_stulist_command(const string& cno, const string& stunum)
{
    string command;
    command = "select * from view_hwcheck_stulist where stu_cno = ";
    command += "\"";
    command += cno;
    command += "\"";
    if (stunum != "all")
    {
        command += " and stu_no = ";
        command += "\"";
        command += stunum;
        command += "\"";
    }

    return command;
}

string get_hwlist_command(const string& cno, const int& chapter, const int& week, const string& filename)
{
    string command;
    string chap_str, week_str;

    if (chapter != -1)
        chap_str = int_to_str(chapter);
    if (week != -1)
        week_str = int_to_str(week);

    command = "select * from view_hwcheck_hwlist where hw_cno = ";
    command += "\"";
    command += cno;
    command += "\"";

    if (chapter != -1)
    {
        command += " and hw_chapter = ";
        command += "\"";
        command += chap_str;
        command += "\"";
    }

    if (week != -1)
    {
        command += " and hw_week = ";
        command += "\"";
        command += week_str;
        command += "\"";
    }

    return command;
}

string get_hwfile_path(const string& srcrootdir, const string& cno, const string& stuno, const string& filename)
{
    return srcrootdir + cno + '-' + stuno + '\\' + filename;
}

void count_filetype(const string& hwfile_check_result, int& correct_num, int& unsub_num, int& utf_num, int& notpdf_num, int& notcom_num, int& not3item_num, int& wrongformat_num, int& comwrong_num)
{
    if (hwfile_check_result == "正确")
        correct_num++;
    else if (hwfile_check_result == "未提交")
        unsub_num++;
    else if (hwfile_check_result == "源文件格式不正确(非GB编码)")
        utf_num++;
    else if (hwfile_check_result == "PDF格式不正确")
        notpdf_num++;
    else if (hwfile_check_result.substr(0, 14) == "首行不是注释行")
        notcom_num++;
    else if (hwfile_check_result.substr(0, 27) == "首行不是符合要求的/* */格式")
        wrongformat_num++;
    else if (hwfile_check_result.substr(0, 12) == "首行不是三项")
        not3item_num++;
    else if (hwfile_check_result.substr(0, 4) == "首行")
        comwrong_num++;
}

int check_stuinfo(const string& line_text, const string& stu_name, const string& stu_no, const string& stu_major, const string& stu_all_major)
{
    if (line_text[0] == '/' && line_text[1] == '/')
    {
        string* item = new(nothrow) string[3];
        if (item == nullptr)
        {
            cout << "No Memory" << endl;
            return false;
        }
        else
        {
            int count_item = 0;
            for (int i = 2; i < (int)line_text.length(); i++)
            {
                while ((line_text[i] == ' ' || line_text[i] == '\t') && i < (int)line_text.length())
                    i++;

                if (i < (int)line_text.length())
                {
                    while (line_text[i] != ' ' && line_text[i] != '\t' && i < (int)line_text.length())
                    {
                        item[count_item] += line_text[i];
                        i++;
                    }
                    count_item++;
                }
                else
                    break;
            }

            bool mark_name = 0;
            bool mark_no = 0;
            bool mark_major = 0;
            int mark = 0;
            for (int i = 0; i < 3; i++)
            {
                if (item[i] == stu_name)
                    mark_name = 1;
                else if (item[i] == stu_no)
                    mark_no = 1;
                else if (item[i] == stu_major)
                    mark_major = 1;
                else if (item[i] == stu_all_major)
                    mark_major = 1;
            }
            delete[]item;

            mark = mark_name * 4 + mark_no * 2 + mark_major;

            return mark;
        }
    }
    else if (line_text[0] == '/' && line_text[1] == '*' && line_text[line_text.length() - 1] == '/' && line_text[line_text.length() - 2] == '*')
    {
        string* item = new(nothrow) string[3];
        if (item == nullptr)
        {
            cout << "No Memory" << endl;
            return false;
        }
        else
        {
            int count_item = 0;
            for (int i = 2; i < (int)line_text.length() - 2; i++)
            {
                while ((line_text[i] == ' ' || line_text[i] == '\t') && i < (int)line_text.length() - 2)
                    i++;

                if (i < (int)line_text.length() - 2)
                {
                    while (line_text[i] != ' ' && line_text[i] != '\t' && i < (int)line_text.length() - 2)
                    {
                        item[count_item] += line_text[i];
                        i++;
                    }
                    count_item++;
                }
                else
                    break;
            }

            bool mark_name = 0;
            bool mark_no = 0;
            bool mark_major = 0;
            int mark = 0;
            for (int i = 0; i < 3; i++)
            {
                if (item[i] == stu_name)
                    mark_name = 1;
                else if (item[i] == stu_no)
                    mark_no = 1;
                else if (item[i] == stu_major)
                    mark_major = 1;
                else if (item[i] == stu_all_major)
                    mark_major = 1;
            }
            delete[]item;

            mark = mark_name * 4 + mark_no * 2 + mark_major;

            return mark;
        }
    }
    else
        return 0;
}

string check_hwfile(const string& action, const string& hwfile_path, const string& hwfile_type, const string& stu_name, const string& stu_no, const string& stu_major, const string& stu_all_major)
{
    if (action == "firstline" && hwfile_type != "h" && hwfile_type != "hpp" && hwfile_type != "c" && hwfile_type != "cpp")
    {
        return "忽略";
    }
    else
    {
        ifstream hwfile(hwfile_path, ios::in);
        if (hwfile.is_open())
        {
            string line_text = get_file_n_line(hwfile, 1);
            string temp_text = get_file_n_line(hwfile, 2);
            temp_text = line_text + temp_text;
            temp_text += get_file_n_line(hwfile, 3);
            temp_text += get_file_n_line(hwfile, 4);
            temp_text += get_file_n_line(hwfile, 5);
            hwfile.close();
            if (hwfile_type == "h" || hwfile_type == "hpp" || hwfile_type == "c" || hwfile_type == "cpp")
            {
                int stuinfo_result = 0;
                if (is_UTF8(temp_text))
                    return  "源文件格式不正确(非GB编码)";
                else if (action == "firstline" && !check_comment(line_text))
                {
                    if (line_text.length() >= 2 && line_text[0] == '/' && line_text[1] == '*' && (line_text[line_text.length() - 1] != '/' || line_text[line_text.length() - 2] != '*'))
                        return "首行不是符合要求的/* */格式 [" + line_text + "]";
                    else
                        return "首行不是注释行 [" + line_text + "]";

                }
                else if (action == "firstline" && check_comment_item_num(line_text) != 3)
                    return "首行不是三项 [" + line_text + "]";
                else if (action == "firstline" && (stuinfo_result = check_stuinfo(line_text, stu_name, stu_no, stu_major, stu_all_major)) != 7)
                {
                    string result = "首行";

                    if ((stuinfo_result & 2) == 0)
                        result += "学号不匹配 ";
                    if ((stuinfo_result & 4) == 0)
                        result += "姓名不匹配 ";
                    if ((stuinfo_result & 1) == 0)
                        result += "班级不匹配 ";
                    result += " [";
                    result += line_text;
                    result += "]";

                    return result;
                }
                else
                    return "正确";
            }
            else if (hwfile_type == "pdf")
            {
                if (is_PDF(line_text))
                    return "正确";
                else
                    return  "PDF格式不正确";
            }
            else if (hwfile_type == "rar")
                return "正确";
            else
                return "非允许文件格式";
        }
        else
        {
            hwfile.close();
            return "未提交";
        }
    }
}

void print_footer(const int& num, const int& correct_num, const int& unsub_num, const int& utf_num, const int& notpdf_num, const int& notcom_num, const int& not3item_num, int& wrongformat_num, const int& comwrong_num, const char& fill_char, const string& filename)
{
    cout << "检查通过" << correct_num << "/" << num << "个";
    if (filename == "all")
        cout << "文件";
    else
        cout << "学生";
    cout << "，本次通过" << correct_num << "个" << endl;

    int frame_length = 15;
    if (utf_num != 0)
        frame_length += 22;
    else if (wrongformat_num != 0)
        frame_length += 18;
    else if (notcom_num != 0)
        frame_length += 10;
    else if (notpdf_num != 0)
        frame_length += 9;
    else if (comwrong_num != 0 || not3item_num != 0)
        frame_length += 8;
    else if (unsub_num != 0)
        frame_length += 2;

    cout << setiosflags(ios::right);
    cout << setfill(fill_char);
    cout << setw(frame_length) << fill_char << endl;
    if (filename == "all")
        cout << "学生";
    cout << "详细信息" << endl;
    cout << setw(frame_length) << fill_char << endl;
    cout << setfill(' ');

    if (correct_num != 0)
        cout << setw(frame_length - 6) << "正确 : " << correct_num << endl;
    if (unsub_num != 0)
        cout << setw(frame_length - 6) << "未提交 : " << unsub_num << endl;
    if(notpdf_num!=0)
        cout << setw(frame_length - 6) << "PDF格式不正确 : " << notpdf_num << endl;
    if (utf_num != 0)
        cout << setw(frame_length - 6) << "源文件格式不正确(非GB编码) : " << utf_num << endl;
    if (wrongformat_num != 0)
        cout << setw(frame_length - 6) << "首行多行注释格式不正确 : " << wrongformat_num << endl;
    if (notcom_num != 0)
        cout << setw(frame_length - 6) << "首行不是注释行 : " << notcom_num << endl;
    if (not3item_num != 0)
        cout << setw(frame_length - 6) << "首行不是三项 : " << not3item_num << endl;
    if (comwrong_num != 0)
        cout << setw(frame_length - 6) << "首行检查出错 : " << comwrong_num << endl;

    cout << setfill(fill_char);
    cout << setw(frame_length) << fill_char << endl;
    cout << setfill(' ');
    cout << endl;

    cout << resetiosflags(ios::right);
}

void print_staresult(const int& stu_num, const int& filesum, const int& correctsum, const int& unsubsum, const int& utfsum, const int& notpdfsum, const int& notcomsum, const int& not3itemsum, const int& wrongformatsum, const int& comwrongsum)
{
    cout << "共完成" << stu_num << "个学生的检查，文件总数:" << filesum << "，通过总数:" << correctsum << "，本次通过" << correctsum << "个" << endl;
    
    int frame_length = 15;
    if (utfsum != 0)
        frame_length += 22;
    else if (wrongformatsum != 0)
        frame_length += 18;
    else if (notcomsum != 0)
        frame_length += 10;
    else if (notpdfsum != 0)
        frame_length += 9;
    else if (comwrongsum != 0 || not3itemsum != 0)
        frame_length += 8;
    else if (unsubsum != 0)
        frame_length += 2;

    cout << setiosflags(ios::right);
    cout << setfill('=');
    cout << setw(frame_length) << '=' << endl;
    cout << "整体详细信息" << endl;
    cout << setw(frame_length) << '=' << endl;
    cout << setfill(' ');

    if (correctsum != 0)
        cout << setw(frame_length - 6) << "正确 : " << correctsum << endl;
    if (unsubsum != 0)
        cout << setw(frame_length - 6) << "未提交 : " << unsubsum << endl;
    if (notpdfsum != 0)
        cout << setw(frame_length - 6) << "PDF格式不正确 : " << notpdfsum << endl;
    if (utfsum != 0)
        cout << setw(frame_length - 6) << "源文件格式不正确(非GB编码) : " << utfsum << endl;
    if (wrongformatsum != 0)
        cout << setw(frame_length - 6) << "首行多行注释格式不正确 : " << wrongformatsum << endl;
    if (notcomsum != 0)
        cout << setw(frame_length - 6) << "首行不是注释行 : " << notcomsum << endl;
    if (not3itemsum != 0)
        cout << setw(frame_length - 6) << "首行不是三项 : " << not3itemsum << endl;
    if (comwrongsum != 0)
        cout << setw(frame_length - 6) << "首行检查出错 : " << comwrongsum << endl;

    cout << setfill('=');
    cout << setw(frame_length) << '=' << endl;
    cout << setfill(' ');
    cout << endl;

    cout << resetiosflags(ios::right);
}

int action_base_firstline_process(const string& action, dbcfg& db_cfg, const string& cno, const string& stunum, const string& filename, const int& chapter, const int& week)
{
    MYSQL* mysql;

    MYSQL_ROW  row_stulist;
    MYSQL_RES* result_stulist;

    MYSQL_ROW  row_hwlist;
    MYSQL_RES* result_hwlist;  

    int stu_num = 0;
    int hw_num = 0;

    if (!init_database(mysql, db_cfg.get_server(), db_cfg.get_user(), db_cfg.get_passwd(), db_cfg.get_name(), db_cfg.get_port()))
    {
        return -1;
    }

    string command_stulist = get_stulist_command(cno, stunum);
    if ((stu_num = get_database_result(mysql, result_stulist, command_stulist)) == -1)
    {
        return -1;
    }

    int i = 0;
    if (filename == "all")
    {
        int filesum = 0;
        int correctsum = 0;
        int unsubsum = 0;
        int utfsum = 0;
        int notpdfsum = 0;
        int notcomsum = 0;
        int not3itemsum = 0;
        int wrongformatsum = 0;
        int comwrongsum = 0;

        string command_hwlist = get_hwlist_command(cno, chapter, week, filename);
        if ((hw_num = get_database_result(mysql, result_hwlist, command_hwlist)) == -1)
        {
            return -1;
        }

        int max_filelen = 0;
        int program_num = 0;

        while ((row_hwlist = mysql_fetch_row(result_hwlist)) != NULL)
        {
            string hwfile_type = get_filetype(row_hwlist[5]);
            max_filelen = (max_filelen <= (int)strlen(row_hwlist[5])) ? strlen(row_hwlist[5]) : max_filelen;
            if (hwfile_type == "h" || hwfile_type == "hpp" || hwfile_type == "c" || hwfile_type == "cpp")
                program_num++;
        }

        if (action == "firstline")
        {
            hw_num = program_num;
        }

        if (hw_num == 0 || stu_num == 0)
        {
            cout << "本次操作的学生数量为0/文件数量为0，未执行" << endl;
            return -1;
        }

        while ((row_stulist = mysql_fetch_row(result_stulist)) != NULL)
        {
            i++;

            int correct_num = 0;
            int unsub_num = 0;
            int utf_num = 0;
            int notpdf_num = 0;
            int notcom_num = 0;
            int not3item_num = 0;
            int wrongformat_num = 0;
            int comwrong_num = 0;

            cout << setiosflags(ios::left);
            cout << setw(3) << i << ": ";

            cout << "学号-" << row_stulist[2] << " ";
            cout << "姓名-" << row_stulist[3] << " ";
            cout << "课号-" << cno << " ";
            cout << "文件数量-" << hw_num;
            cout << endl;

            int n = 0;
            if ((n = get_database_result(mysql, result_hwlist, command_hwlist)) == -1)
            {
                return -1;
            }

            string hwfile_path;
            string hwfile_check_result;
            while ((row_hwlist = mysql_fetch_row(result_hwlist)) != NULL)
            {
                hwfile_path = get_hwfile_path(db_cfg.get_srcrootdir(), cno, row_stulist[2], row_hwlist[5]);
                
                string hwfile_type = get_filetype(row_hwlist[5]);
                string name = row_stulist[3];
                string number = row_stulist[2];
                string major = row_stulist[6];
                string all_major = row_stulist[5];
                
                hwfile_check_result = check_hwfile(action, hwfile_path, hwfile_type, name, number, major, all_major);

                count_filetype(hwfile_check_result, correct_num, unsub_num, utf_num, notpdf_num, notcom_num, not3item_num, wrongformat_num, comwrong_num);

                if (hwfile_check_result != "忽略")
                {
                    cout << "  " << setw(max_filelen) << row_hwlist[5] << " : " << hwfile_check_result;
                    cout << endl;
                }
            }

            print_footer(hw_num, correct_num, unsub_num, utf_num, notpdf_num, notcom_num, not3item_num, wrongformat_num, comwrong_num, '-', filename);

            correctsum += correct_num;
            unsubsum += unsub_num;
            utfsum += utf_num;
            notpdfsum += notpdf_num;
            notcomsum += notcom_num;
            not3itemsum += not3item_num;
            comwrongsum += comwrong_num;
            wrongformatsum += wrongformat_num;
        }

        cout << endl;
        filesum = stu_num * hw_num;
        print_staresult(stu_num, filesum, correctsum, unsubsum, utfsum, notpdfsum, notcomsum, not3itemsum, wrongformatsum, comwrongsum);

        /* 释放result，否则会丢失内存 */
        mysql_free_result(result_hwlist);
    }
    else
    {
        string hwfile_type = get_filetype(filename);

        if (action == "firstline" && hwfile_type != "h" && hwfile_type != "hpp" && hwfile_type != "c" && hwfile_type != "cpp")
        {
            string temp = "首行检查的文件[";
            temp += filename;
            temp += "]必须是源程序文件";
            cout << temp << endl;
        }
        else
        {
            string command_hwlist = get_hwlist_command(cno, chapter, week, filename);
            if ((hw_num = get_database_result(mysql, result_hwlist, command_hwlist)) == -1)
            {
                return -1;
            }

            if (hw_num == 0 || stu_num == 0)
            {
                cout << "本次操作的学生数量为0/文件数量为0，未执行" << endl;
                return -1;
            }

            cout << "课号 : " << cno << " 学生数量 : " << stu_num << " 源文件名 : " << filename << endl;

            int correct_num = 0;
            int unsub_num = 0;
            int utf_num = 0;
            int notpdf_num = 0;
            int notcom_num = 0;
            int not3item_num = 0;
            int wrongformat_num = 0;
            int comwrong_num = 0;

            while ((row_stulist = mysql_fetch_row(result_stulist)) != NULL)
            {
                string hwfile_path = get_hwfile_path(db_cfg.get_srcrootdir(), cno, row_stulist[2], filename);

                string name = row_stulist[3];
                string number = row_stulist[2];
                string major = row_stulist[6];
                string all_major = row_stulist[5];

                string hwfile_check_result = check_hwfile(action, hwfile_path, hwfile_type, name, number, major, all_major);

                count_filetype(hwfile_check_result, correct_num, unsub_num, utf_num, notpdf_num, notcom_num, not3item_num, wrongformat_num, comwrong_num);

                if (hwfile_check_result != "忽略")
                {
                    i++;
                    cout << setiosflags(ios::left);
                    cout << setw(3) << i << ": ";

                    cout << setw(7) << row_stulist[2] << "/";
                    cout << setw(8) << row_stulist[3] << " : ";
                    cout << hwfile_check_result;
                    cout << endl;
                }
            }

            cout << endl;
            print_footer(stu_num, correct_num, unsub_num, utf_num, notpdf_num, notcom_num, not3item_num, wrongformat_num, comwrong_num, '=', filename);

            cout << endl;
        }
    }

    /* 释放result，否则会丢失内存 */
    mysql_free_result(result_stulist);

    /* 关闭整个连接 */
    mysql_close(mysql);

    return 0;
}




string check_2ndline(const string& hwfile_path, const string& name, const string& number, cross_check_list* &cross_list, const int& nth_stu)
{
    ifstream hwfile(hwfile_path, ios::in);
    if (hwfile.is_open())
    {
        string line_text = get_file_n_line(hwfile, 2);
        hwfile.close();
        int stuinfo_result = 0;

        if (is_UTF8(line_text))
        {
            cross_list[nth_stu - 1].set(number, name);
            return  "源文件格式不正确(非GB编码)";
        }
        else if (!check_comment(line_text))
        {
            cross_list[nth_stu - 1].set(number, name);
            return "次行不是注释";
        }
        else
        {
            cross_list[nth_stu - 1].set(number, name, line_text);
            string check_result = cross_list[nth_stu - 1].check();
            return check_result;
        }
    }
    else
    {
        cross_list[nth_stu - 1].set(number, name);
        hwfile.close();
        return "未提交";
    }
}

void count_2ndline_type(const string& hwfile_check_result, int& correct_num, int& unsub_num, int& utf_num, int& notcom_num)
{
    if (hwfile_check_result == "未提交")
        unsub_num++;
    else if (hwfile_check_result == "源文件格式不正确(非GB编码)")
        utf_num++;
    else if (hwfile_check_result == "次行不是注释")
        notcom_num++;
    else
        correct_num++;
}

void print_2ndline_footer(const int& stu_num, const int& correct_num, const int& unsub_num, const int& utf_num, const int& notcom_num)
{
    cout << "检查通过" << correct_num << "/" << stu_num << "个学生";
    cout << "，本次通过" << correct_num << "个" << endl;

    int frame_length = 15;
    if (utf_num != 0)
        frame_length += 22;
    else if (notcom_num != 0)
        frame_length += 8;
    else if (unsub_num != 0)
        frame_length += 2;

    cout << setiosflags(ios::right);
    cout << setfill('=');
    cout << setw(frame_length) << "=" << endl;
    cout << "详细信息" << endl;
    cout << setw(frame_length) << "=" << endl;
    cout << setfill(' ');

    if (correct_num != 0)
        cout << setw(frame_length - 6) << "正确 : " << correct_num << endl;
    if (unsub_num != 0)
        cout << setw(frame_length - 6) << "未提交 : " << unsub_num << endl;
    if (utf_num != 0)
        cout << setw(frame_length - 6) << "源文件格式不正确(非GB编码) : " << utf_num << endl;
    if (notcom_num != 0)
        cout << setw(frame_length - 6) << "次行不是注释 : " << notcom_num << endl;

    cout << setfill('=');
    cout << setw(frame_length) << "=" << endl;
    cout << setfill(' ');
    cout << endl;

    cout << resetiosflags(ios::right);
}

void print_cross_check_result(cross_check_list*& cross_list, const int& stu_num)
{
    cout << setiosflags(ios::left);
    for (int i = 0; i < stu_num; i++)
    {
        cout << setw(3) << i + 1 << ": ";
        cross_list[i].print_cross_check_list(cross_list, stu_num);
    }
}

int action_secondline_process(dbcfg& db_cfg, const string& cno, const string& stunum, const string& filename)
{
    if (stunum != "all")
    {
        cout << "HW_Check_SecondLine 只能针对全体学生" << endl;
        return -1;
    }
    else if (filename == "all")
    {
        cout << "HW_Check_SecondLine 只能针对单文件" << endl;
        return -1;
    }
    else
    {
        string hwfile_type = get_filetype(filename);
        if (hwfile_type != "h" && hwfile_type != "hpp" && hwfile_type != "c" && hwfile_type != "cpp")
        {
            string temp = "次行检查的文件[";
            temp += filename;
            temp += "]必须是源程序文件";
            cout << temp << endl;
            return -1;
        }
        else {
            MYSQL* mysql;

            MYSQL_ROW  row_stulist;
            MYSQL_RES* result_stulist;

            int stu_num = 0;
            int hw_num = 0;

            if (!init_database(mysql, db_cfg.get_server(), db_cfg.get_user(), db_cfg.get_passwd(), db_cfg.get_name(), db_cfg.get_port()))
            {
                return -1;
            }

            string command_stulist = get_stulist_command(cno, stunum);
            if ((stu_num = get_database_result(mysql, result_stulist, command_stulist)) == -1)
            {
                return -1;
            }

            cout << "课号 : " << cno << " 学生数量 : " << stu_num << " 源文件名 : " << filename << endl;

            int correct_num = 0;
            int unsub_num = 0;
            int utf_num = 0;
            int notcom_num = 0;

            cross_check_list* cross_check = new(nothrow) cross_check_list[stu_num];
            if (cross_check == nullptr)
            {
                cout << "No Memory!" << endl;
                return -1;
            }

            int i = 0;
            while ((row_stulist = mysql_fetch_row(result_stulist)) != NULL)
            {
                i++;
                cout << setiosflags(ios::left);
                cout << setw(3) << i << ": ";

                cout << setw(7) << row_stulist[2] << "/";
                cout << setw(8) << row_stulist[3] << " : ";

                string hwfile_path = get_hwfile_path(db_cfg.get_srcrootdir(), cno, row_stulist[2], filename);

                string name = row_stulist[3];
                string number = row_stulist[2];

                string hwfile_check_result = check_2ndline(hwfile_path, name, number, cross_check, i);

                count_2ndline_type(hwfile_check_result, correct_num, unsub_num, utf_num, notcom_num);

                cout << hwfile_check_result;
                cout << endl;
            }

            cout << endl;
            print_2ndline_footer(stu_num, correct_num, unsub_num, utf_num, notcom_num);
            cout << "交叉检查结果：" << endl;

            print_cross_check_result(cross_check, stu_num);

            /* 释放result，否则会丢失内存 */
            mysql_free_result(result_stulist);

            /* 关闭整个连接 */
            mysql_close(mysql);

            delete[]cross_check;

            return 0;
        }
    }
}