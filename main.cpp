#include<fstream>
#include<vector>
#include "lexer.h"

int main()
{
	vector<string> v;
	string temp, output = "";
	int i = 0;
	fstream f, g;
	f.open("testcase.txt", ios::in);
	g.open("output.txt", ios::out);

	g << "Output:" << endl;
	g << "token\t\tlexeme" << endl;

	while (true)
	{
		f >> temp;
		if (f.fail())
			break;
		v.push_back(temp);
		++i;
	}

	for (i = 0; i < v.size(); ++i)
	{
		output = lexer(v.at(i));
		g << output << endl;
	}

	f.close();
	g.close();
	return 0;
}