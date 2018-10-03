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
		if (f.fail())
			break;
		v.push_back(temp);
		++i;
	}

	f.close();
	g.close();
	system("pause");
	return 0;
}