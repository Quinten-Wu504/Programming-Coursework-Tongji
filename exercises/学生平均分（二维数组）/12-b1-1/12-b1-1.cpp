/* 2154146 吴金轩 计科1班 */
#include <iostream>
#include <iomanip>
using namespace std;

#define STUDENT_NUM	4
#define SCORE_NUM	5

/***************************************************************************
  函数名称：
  功    能：求第一门课的平均分
  输入参数：
  返 回 值：
  说    明：相关输出都放在函数中即可
***************************************************************************/
void average(int(*score)[SCORE_NUM])
{
    float avg_1st_grade = 0;
    int(*p)[SCORE_NUM] = score;
    
    for (p = score; p < score + STUDENT_NUM; p++) {
        avg_1st_grade += **p;
    }
    
    avg_1st_grade = avg_1st_grade / STUDENT_NUM;
    cout << endl << "第1门课平均分：" << avg_1st_grade << endl;
}

/***************************************************************************
  函数名称：
  功    能：找出有两门以上课程不及格的学生
  输入参数：
  返 回 值：
  说    明：相关输出都放在函数中即可
***************************************************************************/
void fail(int(*score)[SCORE_NUM])
{
    int(*p_row)[SCORE_NUM] = score;
    int* p_ele = *p_row;
    int num_fail = 0;
    float avg_grade = 0;
    
    cout << endl << "2门以上不及格的学生：" << endl;
    for (p_row = score; p_row < score + STUDENT_NUM; p_row++) {
        num_fail = 0;
        avg_grade = 0;
        
        for (p_ele = *p_row; p_ele < *p_row + SCORE_NUM; p_ele++) {
            if (*p_ele < 60)
                num_fail++;
        }
        
        if (num_fail >= 2) {
            cout << "No：" << p_row - score + 1 << " ";
            for (p_ele = *p_row; p_ele < *p_row + SCORE_NUM; p_ele++) {
                cout << *p_ele << " ";
            }
            cout << "平均：";
            for (p_ele = *p_row; p_ele < *p_row + SCORE_NUM; p_ele++) {
                avg_grade += *p_ele;
            }
            avg_grade = avg_grade / SCORE_NUM;
            cout << avg_grade << endl;
        }
    }
}

/***************************************************************************
  函数名称：
  功    能：找出平均成绩在90分以上或全部成绩在85分以上的学生
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void good(int(*score)[SCORE_NUM])
{
    int(*p_row)[SCORE_NUM] = score;
    int* p_ele = *p_row;
    float avg_grade = 0;
    bool all_over_85 = 1;
    
    cout << endl << "平均90以上或全部85以上的学生：" << endl;
    for (p_row = score; p_row < score + STUDENT_NUM; p_row++) {
        avg_grade = 0;
        all_over_85 = 1;
        for (p_ele = *p_row; p_ele < *p_row + SCORE_NUM; p_ele++) {
            if (*p_ele < 85) {
                all_over_85 = 0;
            }
            avg_grade += *p_ele;
        }
        avg_grade = avg_grade / SCORE_NUM;
        if (all_over_85 || avg_grade >= 90) {
            cout << "No：" << p_row - score + 1 << " ";
            for (p_ele = *p_row; p_ele < *p_row + SCORE_NUM; p_ele++) {
                cout << *p_ele << " ";
            }
            cout << "平均：" << avg_grade << endl;
        }
    }
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
    int a[STUDENT_NUM][SCORE_NUM] = {
        {91, 81, 71, 61, 51},	//第1个学生的1-5门课的成绩
        {92, 82, 72, 32, 52},   //第2个学生的1-5门课的成绩
        {93, 83, 99, 80, 95},   //第3个学生的1-5门课的成绩
        {97, 85, 87, 91, 88} }; //第4个学生的1-5门课的成绩

    int(*p_row)[SCORE_NUM] = a;
    int* p_ele = *p_row;
    
    cout << "初始信息：" << endl;
    for (p_ele = *p_row; p_row < a + STUDENT_NUM; p_row++) {
        cout << "No." << p_row - a + 1 << "的1-5门课成绩：";
        for (; p_ele < *p_row + SCORE_NUM; p_ele++) {
            cout << *p_ele << " ";
        }
        cout << endl;
    }
    
    p_row = a;
    average(p_row);
    fail(p_row);
    good(p_row);
    
    return 0;
}