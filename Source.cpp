//CPSC 323
//Compiler Project
//Frank Ngo & Yifei Feng
//main.cpp

#include<fstream>
#include "IN.h"
#include "LA.h"
#include "SA.h"


int main()
{
	vector<string> input;
	vector<string> token;
	vector<string> output;
	vector<int> line;
	string temp, input_file, output_file;
	int i = 0, j = 0, counter = 1;
	fstream f, g, h;
	string lines;

	//read file
	cout << "CPSC 323 Compiler Project" << endl;
	cout << "Copyright(C) 2018 Frank Ngo & Yifei Feng" << endl << endl;
	cout << "Enter name of input file (*.txt): ";
	getline(cin, input_file);
	cout << "Enter name of output file (*.txt): ";
	getline(cin, output_file);
	f.open(input_file, ios::in);
	g.open(output_file, ios::out);
	h.open(input_file, ios::in);

	while (true)
	{
		f >> temp;
		if (f.fail())
			break;
		input.push_back(temp);
		++i;
	}
	deleteComment(input);
	stringsSeparator(input, token);
	deleteSpace(token);
	//find number of lines
	while (j < token.size())
	{
		getline(h, lines);
		int fs = 0;
		string s;
		int sl;
		while (fs != -1 && line.size() != token.size())
		{
			s = token.at(j);
			fs = lines.find(s);
			if (fs != -1)
			{
				sl = fs + s.length();
				lines.erase(0, sl);
				line.push_back(counter);
			}
			j++;
		}
		j--;
		counter++;
	}
	//syntax analysis and opt
	passVector1(token, line);
	Rat18F();
	passVector2(output);
	//print the assembly code and symbol table
	g << "Address\t\tOperation\tOperand" << endl;
	for (int i = 0; i < I.size(); i++) {
		if (I[i].ope == NULL&&I[i].op!="PUSHI") {
			g << I[i].Iadd << "\t\t" << I[i].op << "\t\t" << endl;
		}
		else
			g << I[i].Iadd << "\t\t" << I[i].op << "\t\t" << I[i].ope << endl;
	}
	g << "Identifier\tMemoryLocation\tType" << endl;
	for (int i = 0; i < S.size(); i++) {
		g << S[i].name << "\t\t" << S[i].Madd << "\t\t" << S[i].type << endl;
	}
	//close file
	f.close();
	g.close();
	h.close();
	cout << endl << "Done... Please refer to " << output_file << endl;
	system("pause");
	return 0;
}