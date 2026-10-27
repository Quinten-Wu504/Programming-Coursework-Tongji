#include <iostream>
#include <cmath>
#include <fstream>
#include <string.h>
using namespace std;

void fun(char(&p)[10][10])
{
	cout << sizeof(p) << endl;;
}

/* main函数不准做任何修改 */
int main()
{
	ofstream out("out.txt", ios::out);

	out << "hello" << endl;

	out.close();

	return 0;
}