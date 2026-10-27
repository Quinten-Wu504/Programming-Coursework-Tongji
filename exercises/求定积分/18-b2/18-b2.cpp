/* 2154146 吴金轩 计科 */
#include <iostream>
#include <cmath>
using namespace std;

/* 从此处到标记替换行之间，给出各种类的定义及实现
	1、不允许定义全局变量（不含const和#define）
	2、不允许添加其它系统头文件
*/
class integral {
protected:
	double low;
	double high;
	int n;
public:
	integral();
	virtual double value() = 0;
	virtual const char* const name() = 0;
	friend istream& operator>>(istream& in, integral& inte);
};

integral::integral()
{
	low = 0;
	high = 0;
	n = 0;
}

istream& operator>>(istream& in, integral& inte)
{
	while (1)
	{
		cout << "请输入" << inte.name() << "的下限、上限及区间划分数量" << endl;
		in >> inte.low >> inte.high >> inte.n;
		if (inte.low <= inte.high && inte.n > 0 && in.good())
			break;
		if (in.fail()) {
			in.clear();
			in.ignore(1000, '\n');
		}
		cout << "数据输入错误，请重新输入" << endl;
	}

	return in;
}

class integral_sin:public integral {
protected:

public:
	integral_sin();
	virtual const char* const name();
	virtual double value();
};

integral_sin::integral_sin() :integral()
{
}

const char* const integral_sin::name()
{
	return "sinxdx";
}

double integral_sin::value()
{
	double sum_area = 0;
	for (int i = 1; i <= n; i++) {
		sum_area += sin(low + i * (high - low) / n) * ((high - low) / n);
	}

	cout << "sinxdx[" << low << "~" << high << "/n=" << n << "] : " << sum_area << endl;

	return sum_area;
}


class integral_cos :public integral {
protected:

public:
	integral_cos();
	virtual const char* const name();
	virtual double value();
};

integral_cos::integral_cos() :integral()
{
}

const char* const integral_cos::name()
{
	return "cosxdx";
}

double integral_cos::value()
{
	double sum_area = 0;
	for (int i = 1; i <= n; i++) {
		sum_area += cos(low + i * (high - low) / n) * ((high - low) / n);
	}

	cout << "cosxdx[" << low << "~" << high << "/n=" << n << "] : " << sum_area << endl;

	return sum_area;
}


class integral_exp :public integral {
protected:

public:
	integral_exp();
	virtual const char* const name();
	virtual double value();
};

integral_exp::integral_exp() :integral()
{
}

const char* const integral_exp::name()
{
	return "e^xdx";
}

double integral_exp::value()
{
	double sum_area = 0;
	for (int i = 1; i <= n; i++) {
		sum_area += exp(low + i * (high - low) / n) * ((high - low) / n);
	}

	cout << "e^xdx[" << low << "~" << high << "/n=" << n << "] : " << sum_area << endl;

	return sum_area;
}

/* -- 替换标记行 -- 本行不要做任何改动 -- 本行不要删除 -- 在本行的下面不要加入任何自己的语句，作业提交后从本行开始会被替换 -- 替换标记行 -- */

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：fun_integral不准动，思考一下，integral应如何定义
***************************************************************************/
void fun_integral(integral& fRef)
{
	cin >> fRef;	//输入上下限、划分数
	cout << fRef.value() << endl;
	return;
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
	integral_sin s1;
	integral_cos s2;
	integral_exp s3;

	fun_integral(s1); //计算sinxdx的值
	fun_integral(s2); //计算cosxdx的值
	fun_integral(s3); //计算expxdx的值

	return 0;
}

//注：矩形计算取右值，输出为正常double格式
