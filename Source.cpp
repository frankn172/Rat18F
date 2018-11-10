//CPSC 323
//Compiler Project
//Frank Ngo & Yifei Feng

#include<fstream>
#include "LA.h"
#include "SA.h"

using namespace std;

int main()
{
	vector<string> input;
	vector<string> token;
	vector<string> output;
	vector<int> line;
	string temp, input_file, output_file;
	int i = 0, counter = 0, start_point, end_point;
	fstream f, g;

	cout << "CPSC 323 Compiler Project" << endl;
	cout << "Copyright(C) 2018 Frank Ngo & Yifei Feng" << endl << endl;

	cout << "Enter name of input file (*.txt): ";
	getline(cin, input_file);
	cout << "Enter name of output file (*.txt): ";
	getline(cin, output_file);
	f.open(input_file, ios::in);
	g.open(output_file, ios::out);

	g << "Output:" << endl;
	g << "token\t\tlexeme" << endl;

	while (true)
	{
		f >> temp;
		if (f.fail())
			break;
		input.push_back(temp);
		++i;
	}


	deleteComment(input);
	sepa(input, token, line);
	deletespace(token);

	passvec1(token);
	Rat18F();
	passvec2(output);
	for (int i = 0; i < output.size(); ++i)
	{
		g << output.at(i) << endl;
	}

	//for (int i = 0; i < token.size(); ++i)
	//{
	//	lexer(output, token.at(i));
	//	g << output.at(i) << endl;
	//}

	f.close();
	g.close();
	cout << endl << "Done... Please refer to " << output_file << endl;
	system("pause");
	return 0;
}
