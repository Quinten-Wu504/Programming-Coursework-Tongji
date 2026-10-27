/* 2154146 吴金轩 计科1班 */
#include <iostream>
using namespace std;

int main()
{
	const char* month[] = { "January", "February", "March","April","May","June", "July", "August", "September", "October", "November", "December" };
	int num_month, a;
	cout << "请输入月份(1-12)" << endl;
	cin >> num_month;
	if (cin.fail() || num_month < 1 || num_month > 12 || ((a = getchar()) != 10 && a != 32))
		cout << "Invalid" << endl;
	else
		cout << month[num_month - 1] << endl;
	return 0;
}