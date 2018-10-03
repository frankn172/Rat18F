#include<iostream>
#include<string>
using namespace std;

bool isKeyword(string input)
{
	string keywords[14] = { "function","int","boolean","real","if","ifend","else","return","put","get","while","whileend","true","false" };
	for (int i = 0; i < 14; i++)
	{
		if (input.compare(keywords[i]) == 0)
			return true;
	}
	return false;
}

bool isOperator(string input)
{
	string operators[11] = { "=","+","-","*","/","==","^=",">","<","=>","=<" };
	for (int i = 0; i < 11; i++)
	{
		if (input.compare(operators[i]) == 0)
			return true;
	}
	return false;
}

bool isSeparator(string input)
{
	string separators[9] = { "<",">",":","$$",",",";","(",")","|" };
	for (int i = 0; i < 9; i++)
	{
		if (input.compare(separators[i]) == 0)
			return true;
	}
	return false;
}

bool isInteger(string input)
{
	string::const_iterator it = input.begin();
	while ((it != input.end()) && (isdigit(*it)))
		++it;
	return (!input.empty() && it == input.end());
}

bool isReal(string input)
{
	string delimiter = ".";
	string before = input.substr(0, input.find(delimiter));
	string after = input.substr(input.find(delimiter) + 1, input.size() + 1);
	return ((isInteger(before)) && (isInteger(after)));
}