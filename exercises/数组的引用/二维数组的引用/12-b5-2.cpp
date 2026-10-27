/* 计科 2154146 吴金轩 */
#include <iostream>
#include <iomanip>
using namespace std;

const char* sp = "=====================================";

/***************************************************************************
  函数名称：matrix_print
  功    能：打印矩阵
  输入参数：const char* s：提示语句的常量字符串
			T& matrix_input：需要输出的矩形
  返 回 值：无
  说    明：每个数字宽度为8，右对齐
***************************************************************************/
template<typename T>
void matrix_print(const char* s, T& matrix_input)
{
	cout << s << endl;
	int matrix_line = sizeof(T) / sizeof(*matrix_input), matrix_colunm = sizeof(*matrix_input) / sizeof(**matrix_input);
	for (int i = 0; i < matrix_line; i++) {
		for (int j = 0; j < matrix_colunm; j++) {
			cout << setiosflags(ios::right) << setw(8) << *(*(matrix_input + i) + j);
		}
		cout << endl;
	}
	cout << resetiosflags(ios::right);
	return;
}

/***************************************************************************
  函数名称：matrix_addition
  功    能：实现矩阵加法
  输入参数：T0& matrix_result：保存结果的矩阵
			T1& matrix_input_1：加法矩阵1
			T2& matrix_input_2：加法矩阵2
  返 回 值：无
  说    明：无
***************************************************************************/
template<typename T0, typename T1, typename T2>
void matrix_addition(T0& matrix_result, T1& matrix_input_1, T2& matrix_input_2)
{
	int matrix_line[3] = { sizeof(T0) / sizeof(*matrix_result), sizeof(T1) / sizeof(*matrix_input_1), sizeof(T2) / sizeof(*matrix_input_2) };
	int matrix_colunm[3] = { sizeof(*matrix_result) / sizeof(**matrix_result), sizeof(*matrix_input_1) / sizeof(**matrix_input_1), sizeof(*matrix_input_2) / sizeof(**matrix_input_2) };
	cout << setiosflags(ios::left);
	cout << "源矩阵1 : 行=" << setw(2) << *(matrix_line + 1) << "列=" << setw(2) << *(matrix_colunm + 1) << "占用空间=" << sizeof(matrix_input_1) << "字节" << endl;
	cout << "源矩阵2 : 行=" << setw(2) << *(matrix_line + 2) << "列=" << setw(2) << *(matrix_colunm + 2) << "占用空间=" << sizeof(matrix_input_2) << "字节" << endl;
	cout << "和矩阵  : 行=" << setw(2) << *matrix_line << "列=" << setw(2) << *matrix_colunm << "占用空间=" << sizeof(matrix_result) << "字节" << endl;

	if (*matrix_line != *(matrix_line + 1) || *(matrix_line + 1) != *(matrix_line + 2) || *matrix_line != *(matrix_line + 2)) {
		cout << "矩阵不匹配" << endl;
	}
	else {
		for (int i = 0; i < *matrix_line; i++) {
			for (int j = 0; j < *matrix_colunm; j++) {
				*(*(matrix_result + i) + j) = *(*(matrix_input_1 + i) + j) + *(*(matrix_input_2 + i) + j);
			}
		}
	}

	return;
}


/***************************************************************************
  函数名称：matrix_multiplication
  功    能：实现矩阵乘法
  输入参数：T0& matrix_result：保存结果的矩阵
			T1& matrix_input_1：乘法矩阵1
			T2& matrix_input_2：乘法矩阵2
  返 回 值：无
  说    明：无
***************************************************************************/
template<typename T0, typename T1, typename T2>
void matrix_multiplication(T0& matrix_result, T1& matrix_input_1, T2& matrix_input_2)
{
	int matrix_line[3] = { sizeof(T0) / sizeof(*matrix_result), sizeof(T1) / sizeof(*matrix_input_1), sizeof(T2) / sizeof(*matrix_input_2) };
	int matrix_colunm[3] = { sizeof(*matrix_result) / sizeof(**matrix_result), sizeof(*matrix_input_1) / sizeof(**matrix_input_1), sizeof(*matrix_input_2) / sizeof(**matrix_input_2) };
	cout << "源矩阵1 : 行=" << setw(2) << *(matrix_line + 1) << "列=" << setw(2) << *(matrix_colunm + 1) << "占用空间=" << sizeof(matrix_input_1) << "字节" << endl;
	cout << "源矩阵2 : 行=" << setw(2) << *(matrix_line + 2) << "列=" << setw(2) << *(matrix_colunm + 2) << "占用空间=" << sizeof(matrix_input_2) << "字节" << endl;
	cout << "积矩阵  : 行=" << setw(2) << *matrix_line << "列=" << setw(2) << *matrix_colunm << "占用空间=" << sizeof(matrix_result) << "字节" << endl;

	if (*(matrix_line + 2) != *(matrix_colunm + 1)) {
		cout << "矩阵不匹配" << endl;
	}
	else {
		for (int i = 0; i < *(matrix_line + 0); i++) {
			for (int j = 0; j < *(matrix_colunm + 0); j++) {
				*(*(matrix_result + i) + j) = 0;
				for (int p = 0; p < *(matrix_colunm + 1); p++) {
					*(*(matrix_result + i) + j) += *(*(matrix_input_1 + i) + p) * *(*(matrix_input_2 + p) + j);
				}
			}
		}
	}
	return;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数不准更改
***************************************************************************/
int main()
{
	int t1[3][4] = {
		{1,2,3,4},
		{5,6,7,8},
		{9,10,11,12}
	};
	int t2[3][4] = {
		{12,11,10,9},
		{8,7,6,5},
		{4,3,2,1}
	};
	int t3[4][2] = {
		{1, 2},
		{3, 4},
		{5, 6},
		{7, 8}
	};
	int t_add[3][4], t_mul[3][2];

	cout << sp << endl;
	matrix_print("加法运算，源矩阵1：", t1);
	matrix_print("加法运算，源矩阵2：", t2);
	matrix_addition(t_add, t1, t2);	//将t1和t2的和放入t_add中，人工保证三个矩阵行列一致
	matrix_print("加法运算，和矩阵 ：", t_add);
	cout << sp << endl;
	matrix_print("乘法运算，源矩阵1：", t1);
	matrix_print("乘法运算，源矩阵2：", t3);
	matrix_multiplication(t_mul, t1, t3);	//将t1和t2的和放入t_add中，人工保证三个矩阵行列一致
	matrix_print("乘法运算，积矩阵 ：", t_mul);
	cout << sp << endl;

	double d1[2][4] = {
		{1.1, 2.2, 3.3, 4.4},
		{5.5 ,6.6, 7.7, 8.8}
	};
	double d2[2][4] = {
		{8.8, 7.7, 6.6, 5.5},
		{4.4, 3.3, 2.2, 1.1}
	};
	double d_add[2][4];
	/* 不要问为什么矩阵乘法数据类型不同，故意的 */
	float f3[4][3] = {
		{12.12f, 11.11f, 10.10f},
		{9.9f, 8.8f, 7.7f},
		{6.6f, 5.5f, 4.4f},
		{3.3f, 2.2f, 1.1f}
	};
	int i_mul[2][3];

	matrix_print("加法运算，源矩阵1：", d1);
	matrix_print("加法运算，源矩阵2：", d2);
	matrix_addition(d_add, d1, d2);	//将d1和d2的和放入d_add中，人工保证三个矩阵行列一致
	matrix_print("加法运算，和矩阵 ：", d_add);
	cout << sp << endl;
	matrix_print("乘法运算，源矩阵1：", d1);
	matrix_print("乘法运算，源矩阵2：", f3);
	matrix_multiplication(i_mul, d1, f3);	//将t1和t2的和放入t_add中，人工保证三个矩阵行列一致
	matrix_print("乘法运算，积矩阵 ：", i_mul);
	cout << sp << endl;

	return 0;
}