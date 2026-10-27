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
  说    明：
***************************************************************************/
void average(int(*score)[STUDENT_NUM])
{
    int* p = *score;
    float avg_1st_grade = 0;
    for (p = *score; p < *score + STUDENT_NUM; p++) {
        avg_1st_grade += *p;
    }
    avg_1st_grade /= STUDENT_NUM;
    cout << endl << "第1门课平均分：" << avg_1st_grade << endl;
}

/***************************************************************************
  函数名称：
  功    能：找出有两门以上课程不及格的学生
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void fail(int(*score)[STUDENT_NUM])
{
    int(*p_row)[STUDENT_NUM] = score, * p_ele;
    int i = 0;
    float avg_score = 0;
    int num_fail = 0;
    cout << endl << "2门以上不及格的学生：" << endl;
    for (i = 0; i < 4; i++) {
        num_fail = 0;
        avg_score = 0;
        for (p_row = score; p_row < score + SCORE_NUM; p_row++) {
            p_ele = *p_row + i;
            if (*p_ele < 60)
                num_fail++;
        }
        if (num_fail >= 2) {
            cout << "No：" << i + 1 << " ";
            for (p_row = score; p_row < score + SCORE_NUM; p_row++) {
                p_ele = *p_row + i;
                avg_score += *p_ele;
                cout << *p_ele << " ";
            }
            avg_score /= SCORE_NUM;
            cout << "平均：" << avg_score << endl;
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
void good(int(*score)[STUDENT_NUM])
{
    int(*p_row)[STUDENT_NUM] = score, * p_ele;
    int i = 0;
    float avg_grade = 0;
    bool all_over_85 = 1;
    cout << endl << "平均90以上或全部85以上的学生：" << endl;
    for (i = 0; i < STUDENT_NUM; i++) {
        avg_grade = 0;
        all_over_85 = 1;

        for (p_row = score; p_row < score + SCORE_NUM; p_row++) {
            p_ele = *p_row + i;
            avg_grade += *p_ele;
            if (*p_ele < 85)
                all_over_85 = 0;
        }

        avg_grade /= SCORE_NUM;
        
        if (avg_grade >= 90 || all_over_85) {
            cout << "No：" << i + 1 << " ";
            for (p_row = score; p_row < score + SCORE_NUM; p_row++) {
                p_ele = *p_row + i;
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
    int a[SCORE_NUM][STUDENT_NUM] = {
        {91,92,93,97},  //第1-4个学生的第1门课成绩
        {81,82,83,85},  //第1-4个学生的第2门课成绩
        {71,72,99,87},  //第1-4个学生的第3门课成绩
        {61,32,80,91},  //第1-4个学生的第4门课成绩
        {51,52,95,88} };//第1-4个学生的第5门课成绩

    int(*p_row)[STUDENT_NUM] = a;
    int* p_ele = *p_row;

    cout << "初始信息：" << endl;
    for (p_row = a; p_row < a + SCORE_NUM; p_row++) {
        cout << "No.1-4学生的第" << p_row - a + 1 << "门课的成绩：";
        for (p_ele = *p_row; p_ele < *p_row + STUDENT_NUM; p_ele++) {
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