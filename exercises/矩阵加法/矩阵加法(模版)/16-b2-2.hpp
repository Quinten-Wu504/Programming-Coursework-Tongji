/* 2154146 Îâ½ðÐù ¼Æ¿Æ1°à */
#include <iostream>
#include <string>
using namespace std;

template<typename T, const int ROW, const int COL>
class matrix {
private:
	
	T value[ROW][COL];
public:
	matrix(const int(*p)[COL])
	{
		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COL; j++) {
				value[i][j] = p[i][j];
			}
		}
	}

	matrix()
	{
	}

	friend matrix<T, ROW, COL> operator+(const matrix<T, ROW, COL>& a, const matrix<T, ROW, COL>& b)
	{
		matrix<T, ROW, COL> c;

		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COL; j++) {
				c.value[i][j] = a.value[i][j] + b.value[i][j];
			}
		}

		return c;
	}

	friend istream& operator>>(istream& in, matrix<T, ROW, COL>& a)
	{
		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COL; j++) {
				in >> a.value[i][j];
			}
		}

		return in;
	}

	friend ostream& operator<<(ostream& out, const matrix<T, ROW, COL>& a)
	{
		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COL; j++) {
				out << a.value[i][j] << " ";
			}
			out << endl;
		}

		return out;
	}
};