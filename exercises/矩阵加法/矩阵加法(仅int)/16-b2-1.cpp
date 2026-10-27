/* 2154146 吴金轩 计科1班 */
#include <iostream>
using namespace std;

const int ROW = 2;
const int COL = 3;

#define OPERATOR_IS_MENBER_FUNCTION		1	//运算符的重载用成员函数方式实现（如果值为0，表示用友元方式实现）
/* !@#$%^&*() 替换分隔线，本行及之前行的内容均会被替换，除了第8行的修改0/1之外，不要加自己的内容 )(*&^%$#@! */

class matrix {
private:
	int value[ROW][COL];
public:
	matrix(const int(*p)[COL]);	//构造函数，用数组初始化矩阵
	matrix();

#if OPERATOR_IS_MENBER_FUNCTION
	matrix operator+(matrix& b);
#else
	friend matrix operator+(matrix& a, matrix& b);
#endif

	friend istream& operator>>(istream& in, matrix& a);
	friend ostream& operator<<(ostream& out, const matrix& a);
};

matrix::matrix()
{
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			value[i][j] = 0;
		}
	}
}

matrix::matrix(const int(*p)[COL])
{
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			value[i][j] = p[i][j];
		}
	}
}

#if OPERATOR_IS_MENBER_FUNCTION
matrix matrix::operator+(matrix& b)
{
	matrix c;

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			c.value[i][j] = value[i][j] + b.value[i][j];
		}
	}

	return c;
}

#else
matrix operator+(matrix& a, matrix& b)
{
	matrix c;

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			c.value[i][j] = a.value[i][j] + b.value[i][j];
		}
	}

	return c;
}

#endif

istream& operator>>(istream& in, matrix& a)
{
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			in >> a.value[i][j];
		}
	}

	return in;
}

ostream& operator<<(ostream& out, const matrix& a)
{
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			out << a.value[i][j] << " ";
		}
		out << endl;
	}

	return out;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数不准动
***************************************************************************/
int main()
{
	int a[ROW][COL] = { { 1,2,3 },{ 4,5,6 } };
	int b[ROW][COL] = { { 2,4,6 },{ 3,6,9 } };
	matrix m1(a), m2(b), m3; //m3的初值为全0

	/* 下面为定值测试 */
	cout << "初始矩阵m1的值" << endl;
	cout << m1 << endl;
	cout << "初始矩阵m2的值" << endl;
	cout << m2 << endl;

	m3 = m1 + m2;
	cout << "相加后矩阵m3的值" << endl;
	cout << m3 << endl;

	cout << "------------------" << endl;

	/* 下面为键盘输入测试 */
	cout << "请输入初始矩阵m1" << endl;
	cin >> m1;
	cout << "请输入初始矩阵m2" << endl;
	cin >> m2;

	cout << "初始矩阵m1的值" << endl;
	cout << m1 << endl;
	cout << "初始矩阵m2的值" << endl;
	cout << m2 << endl;
	cout << "相加后矩阵m3的值" << endl;
	cout << (m3 = m1 + m2) << endl;

	return 0;
}