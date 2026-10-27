/* 2154146 吴金轩 计科 */
#include <iostream>
using namespace std;

/***************************************************************************
  函数名称：rotate_matrix
  功    能：对方阵进行旋转操作（矩阵元素类型为int）
  输入参数：int* p_matrix_start：方阵的首元素的地址
            int n：方阵的阶数
  返 回 值：无
  说    明：无
***************************************************************************/
void rotate_matrix(int* p_matrix_start, int n)
{
    int temp_num = 0;
    // 水平翻转
    for (int i = 0; i < n / 2; ++i) {
        for (int j = 0; j < n; ++j) {
            temp_num = p_matrix_start[i * n + j];
            p_matrix_start[i * n + j] = p_matrix_start[(n - i - 1) * n + j];
            p_matrix_start[(n - i - 1) * n + j] = temp_num;
        }
    }
    // 主对角线翻转
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            temp_num = p_matrix_start[i * n + j];
            p_matrix_start[i * n + j] = p_matrix_start[j * n + i];
            p_matrix_start[j * n + i] = temp_num;
        }
    }
}

/***************************************************************************
  函数名称：rotate_matrix
  功    能：对方阵进行旋转操作（矩阵元素类型为bool）
  输入参数：bool* p_matrix_start：方阵的首元素的地址
            int n：方阵的阶数
  返 回 值：无
  说    明：无
***************************************************************************/
void rotate_matrix(bool* p_matrix_start, int n)
{
    bool temp_num = 0;
    // 水平翻转
    for (int i = 0; i < n / 2; ++i) {
        for (int j = 0; j < n; ++j) {
            temp_num = p_matrix_start[i * n + j];
            p_matrix_start[i * n + j] = p_matrix_start[(n - i - 1) * n + j];
            p_matrix_start[(n - i - 1) * n + j] = temp_num;
        }
    }
    // 主对角线翻转
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            temp_num = p_matrix_start[i * n + j];
            p_matrix_start[i * n + j] = p_matrix_start[j * n + i];
            p_matrix_start[j * n + i] = temp_num;
        }
    }
}