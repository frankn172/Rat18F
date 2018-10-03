#include<fstream>
#include<vector>
#include "lexer.h"

int main()
{
	vector<string> v;
	string temp;
	int i = 0;
	fstream f, g;
	f.open("testcase.txt", ios::in);
	g.open("output.txt", ios::out);

	while (true)
	{
		f >> temp;
		v.push_back(temp);
		if (f.fail())
			break;
		++i;
	}

	f.close();
	g.close();
	system("pause");
	return 0;
}