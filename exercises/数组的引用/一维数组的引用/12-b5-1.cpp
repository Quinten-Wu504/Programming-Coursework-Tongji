/* 计科 2154146 吴金轩 */
#include <iostream>
using namespace std;

/***************************************************************************
  函数名称：test
  功    能：输出传入数组的大小
  输入参数：T& array：数组
  返 回 值：无
  说    明：无
***************************************************************************/
template<typename T>
void test(T& array)
{
	cout << sizeof(array) << endl;
}

/***************************************************************************
  函数名称：tj_strcpy_s
  功    能：安全地将原数组中第一个'\0'前的字符复制到目标数组中
  输入参数：T1& dst：目标数组
			T2& src：原数组
  返 回 值：char*：目标数组的地址
  说    明：无
***************************************************************************/
template<typename T1, typename T2>
char* tj_strcpy_s(T1& dst, T2& src)
{
	char* d = dst;		//dst为要复制的目标串
	const char* s = src;	//src为要复制的源串

	while (*s != '\0' && d - dst < int(sizeof(dst)) - 1)
		*d++ = *s++;
	*d = '\0';

	return dst;
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
	int t1[10];
	double t2[20];
	test(t1);	//期望输入40
	test(t2);	//期望输出160

	char s1[10], s2[20];
	const char* s = "Welcome to Tongji University!";
	cout << tj_strcpy_s(s1, s) << '*' << endl; //期望输出：Welcome t*
	cout << tj_strcpy_s(s2, s) << '*' << endl; //期望输出：Welcome to Tongji U*

	return 0;
}