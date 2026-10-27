#include "class_cross_check_list.h"

cross_check_list::cross_check_list() :stuinfo()
{
    number = 0;
    list = nullptr;
}

cross_check_list::cross_check_list(const string& hostno, const string& hostname, const string& comment_text) :stuinfo(hostno, hostname)
{
	number = (check_comment_item_num(comment_text) + 1) / 2;
	list = new(nothrow) stuinfo[number];
    if (list == nullptr)
    {
        cout << "No Memory!" << endl;
        return;
    }

    if (comment_text[0] == '/' && comment_text[1] == '/')
    {
        int count_item = 0;
        for (int i = 2; i < (int)comment_text.length(); i++)
        {
            while ((comment_text[i] == ' ' || comment_text[i] == '\t') && i < (int)comment_text.length())
                i++;

            if (i < (int)comment_text.length())
            {
                while (comment_text[i] != ' ' && comment_text[i] != '\t' && i < (int)comment_text.length())
                {
                    if (count_item % 2 == 0)
                        list[count_item / 2].append_stuno(comment_text[i]);
                    else
                        list[count_item / 2].append_stuname(comment_text[i]);
                    i++;
                }
                count_item++;
            }
            else
                break;
        }
    }
    else if (comment_text[0] == '/' && comment_text[1] == '*' && comment_text[comment_text.length() - 1] == '/' && comment_text[comment_text.length() - 2] == '*')
    {
        int count_item = 0;
        for (int i = 2; i < (int)comment_text.length() - 2; i++)
        {
            while ((comment_text[i] == ' ' || comment_text[i] == '\t') && i < (int)comment_text.length() - 2)
                i++;

            if (i < (int)comment_text.length() - 2)
            {
                while (comment_text[i] != ' ' && comment_text[i] != '\t' && i < (int)comment_text.length() - 2)
                {
                    if (count_item % 2 == 0)
                        list[count_item / 2].append_stuno(comment_text[i]);
                    else
                        list[count_item / 2].append_stuname(comment_text[i]);
                    i++;
                }
                count_item++;
            }
            else
                break;
        }
    }
}

cross_check_list::~cross_check_list()
{
    if (list != nullptr)
        delete[]list;
}

void cross_check_list::set(const string& hostno, const string& hostname)
{
    stuno = hostno;
    stuname = hostname;
    number = 0;
    list = nullptr;
}

void cross_check_list::set(const string& hostno, const string& hostname, const string& comment_text)
{
    stuno = hostno;
    stuname = hostname;
    number = (check_comment_item_num(comment_text) + 1) / 2;

    if (list != nullptr)
        delete[]list;

    list = new(nothrow) stuinfo[number];
    if (list == nullptr)
    {
        cout << "No Memory!" << endl;
        return;
    }

    if (comment_text[0] == '/' && comment_text[1] == '/')
    {
        int count_item = 0;
        for (int i = 2; i < (int)comment_text.length(); i++)
        {
            while ((comment_text[i] == ' ' || comment_text[i] == '\t') && i < (int)comment_text.length())
                i++;

            if (i < (int)comment_text.length())
            {
                while (comment_text[i] != ' ' && comment_text[i] != '\t' && i < (int)comment_text.length())
                {
                    if (count_item % 2 == 0)
                        list[count_item / 2].append_stuno(comment_text[i]);
                    else
                        list[count_item / 2].append_stuname(comment_text[i]);
                    i++;
                }
                count_item++;
            }
            else
                break;
        }
    }
    else if (comment_text[0] == '/' && comment_text[1] == '*' && comment_text[comment_text.length() - 1] == '/' && comment_text[comment_text.length() - 2] == '*')
    {
        int count_item = 0;
        for (int i = 2; i < (int)comment_text.length() - 2; i++)
        {
            while ((comment_text[i] == ' ' || comment_text[i] == '\t') && i < (int)comment_text.length() - 2)
                i++;

            if (i < (int)comment_text.length() - 2)
            {
                while (comment_text[i] != ' ' && comment_text[i] != '\t' && i < (int)comment_text.length() - 2)
                {
                    if (count_item % 2 == 0)
                        list[count_item / 2].append_stuno(comment_text[i]);
                    else
                        list[count_item / 2].append_stuname(comment_text[i]);
                    i++;
                }
                count_item++;
            }
            else
                break;
        }
    }
}

string cross_check_list::check()
{
    string temp = "";
    int i = 0;
    for (i = 0; i < number; i++)
    {
        if (!list[i].check_stuno())
        {
            if (list[i].get_stuname() != "")
            {
                temp += "第";
                temp += int_to_str(i + 1);
                temp += "位同学的学号[";
                temp += list[i].get_stuno();
                temp += "]不是7位，后续内容忽略";
                break;
            }
            else
            {
                temp += "第[";
                temp += int_to_str(i);
                temp += "]个学生后面的信息不全(只读到一项)，后续内容忽略";
                break;
            }
        }
        else
        {
            if (list[i].get_stuname() != "")
            {
                if (list[i].get_stuno() == stuno || list[i].get_stuname() == stuname)
                {
                    temp += "第[";
                    temp += int_to_str(i + 1);
                    temp += "]项写了自己，后续内容忽略";
                    break;
                }
            }
            else
            {
                temp += "第[";
                temp += int_to_str(i);
                temp += "]个学生后面的信息不全(只读到一项)，后续内容忽略";
                break;
            }
        }
    }

    if (i == number)
    {
        return "正确";
    }
    else
    {
        for (i; i < number; i++)
        {
            list[i].set("", "");
        }
        return temp;
    }
}

void cross_check_list::print_cross_check_list(cross_check_list*& cross_list, int stu_num)
{
    cout << stuno << " " << stuname << endl;
    for (int i = 0; i < number && list[i].get_stuno() != ""; i++)
    {
        cout << "\t" << list[i].get_stuno() << " " << list[i].get_stuname() << "\t";
        int stuno_loc = find_stuno(cross_list, list[i].get_stuno(), stu_num);
        if (stuno_loc == -1)
            cout << "对方学号不存在" << endl;
        else
        {
            if (cross_list[stuno_loc].get_stuname() != list[i].get_stuname())
                cout << "对方姓名不正确" << endl;
            else
            {
                int j = 0;
                for (j = 0; j < cross_list[stuno_loc].number && cross_list[stuno_loc].list[j].get_stuno() != ""; j++)
                {
                    if (cross_list[stuno_loc].list[j].get_stuno() == stuno)
                        break;
                }

                if (j == cross_list[stuno_loc].number || cross_list[stuno_loc].list[j].get_stuno() == "")
                    cout << "抛弃了你" << endl;
                else
                {
                    if (cross_list[stuno_loc].list[j].get_stuname() == stuname)
                        cout << endl;
                    else
                        cout << "没写对你名字" << endl;
                }
            }
        }
    }
}

int find_stuno(cross_check_list*& cross_list, string stuno, int stu_num)
{
    int i = 0;
    for (i = 0; i < stu_num; i++)
    {
        if (cross_list[i].get_stuno() == stuno)
            break;
    }

    if (i == stu_num)
        return -1;
    else
        return i;
}