//CPSC 323
//Compiler Project
//Frank Ngo & Yifei Feng

#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;

bool isKeyword(string input)
{
	string keywords[14] = { "function","int","boolean","real","if","ifend","else","return","put","get","while","whileend","true","false" };
	for (int i = 0; i < 14; ++i)
	{
		if (input.compare(keywords[i]) == 0)
			return true;
	}
	return false;
}

bool isOperator(string input)
{
	string operators[11] = { "=","+","-","*","/","==","^=",">","<","=>","=<" };
	for (int i = 0; i < 11; ++i)
	{
		if (input.compare(operators[i]) == 0)
			return true;
	}
	return false;
}

bool isSeparator(string input)
{
	string separators[9] = { ":","$$",",",";","(",")","|","{","}" };
	for (int i = 0; i < 9; ++i)
	{
		if (input.compare(separators[i]) == 0)
			return true;
	}
	return false;
}

bool isInteger(string input)
{
	int table[2][1] = { 1,1 };
	int state = 0;
	int col;
	for (int i = 0; i < input.length(); i++)
	{
		if (isdigit(input[i]))
		{
			col = 0;
		}
		else { return false; }
		state = table[state][col];
	}
	if (state == 1)
	{
		return true;
	}
	return false;
}

bool isReal(string input)
{
	int table[4][2] = { 1,0,1,2,3,0,3,0 };
	int state = 0;
	int col;
	for (int i = 0; i < input.length(); i++)
	{
		if (isdigit(input[i]))
		{
			col = 0;
		}
		else if (input[i] == '.')
		{
			col = 1;
		}
		else return false;
		state = table[state][col];
	}
	if (state == 3)
	{
		return true;
	}
	return false;
}

bool isIdentifier(string input)
{
	int table[4][2] = { 1,0,2,3,2,3,2,3 };
	int state = 0;
	int col;
	for (int i = 0; i < input.length(); i++)
	{
		if (isalpha(input[i]))
		{
			col = 0;
		}
		else if (isdigit(input[i]))
		{
			col = 1;
		}
		else
		{
			return false;
		}
		state = table[state][col];
	}
	if (state == 1 || state == 2)
	{
		return true;
	}
	return false;
}

//delete comments inclosed in "[*" and "*]" from a string vector
void deleteComment(vector<string> &str)
{
	int counter, start_point, end_point;
	while (true)
	{
		counter = 0;
		for (int i = 0; i < str.size(); ++i)
		{
			if (str.at(i).compare("[*") == 0)
			{
				start_point = i;
				counter++;
			}
			if (str.at(i).compare("*]") == 0)
			{
				end_point = i;
				counter++;
			}
		}
		if (counter != 0)
			str.erase(str.begin() + start_point, str.begin() + end_point + 1);
		else break;
	}
}

//check if it is two connected OP/SEP
bool isTwo(string input)
{
	string temp = input;
	string twocase[5] = { "==","^=","=<","=>","$$" };
	for (int i = 0; i < 5; ++i)
	{
		if (temp == twocase[i])
			return true;
	}
	return false;
}


void lexer(vector<string> r, string input)
{
	string::const_iterator fir = input.begin();
	//go to special case if not match common case
	if (isdigit(*fir))
	{
		if (isInteger(input))
			r.push_back("Integer\t\t" + input);
		else if (isReal(input))
			r.push_back("real\t\t" + input);
	}
	else if (isalpha(*fir))
	{
		if (isKeyword(input))
			r.push_back("keyword\t\t" + input);
		else if (isIdentifier(input))
			r.push_back("identifier\t" + input);
	}
	else
	{
		if (isSeparator(input))
			r.push_back("separator\t" + input);
		else if (isOperator(input))
			r.push_back("operator\t" + input);
		else
			r.push_back("illegal\t\t" + input);
	}
}