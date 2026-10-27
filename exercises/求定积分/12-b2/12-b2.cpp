/* 2154146 吴金轩 计科1班 */ 
#include <iostream>
#include<cmath>
using namespace std;

double definite_integration(double (*f_cmath)(double), double low, double high, int n)
{
	double sum_area = 0;
	for (int i = 1; i <= n; i++) {
		sum_area += f_cmath(low + i * (high - low) / n) * ((high - low) / n);
	}
	return sum_area;
}

int main()
{
	int n;
	double low, high, value;
	
	cout << "请输入sinxdx的下限、上限及区间划分数量" << endl;
	cin >> low >> high >> n;
	value = definite_integration(sin, low, high, n);//sin为cmath中已有函数
	cout << "sinxdx[" << low << "~" << high << "/n=" << n << "] : " << value << endl;

	cout << "请输入cosxdx的下限、上限及区间划分数量" << endl;
	cin >> low >> high >> n;
	value = definite_integration(cos, low, high, n);//cos为cmath中已有函数
	cout << "cosxdx[" << low << "~" << high << "/n=" << n << "] : " << value << endl;

	cout << "请输入e^xdx的下限、上限及区间划分数量" << endl;
	cin >> low >> high >> n;
	value = definite_integration(exp, low, high, n);//exp为cmath中已有函数
	cout << "e^xdx[" << low << "~" << high << "/n=" << n << "] : " << value << endl;
	return 0;
}
