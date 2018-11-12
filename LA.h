//CPSC 323
//Compiler Project
//Frank Ngo & Yifei Feng
//LA.h

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
			col = 0;
		else
			return false;
		state = table[state][col];
	}
	if (state == 1)
		return true;
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
			col = 0;
		else if (input[i] == '.')
			col = 1;
		else
			return false;
		state = table[state][col];
	}
	if (state == 3)
		return true;
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
			col = 0;
		else if (isdigit(input[i]))
			col = 1;
		else
			return false;
		state = table[state][col];
	}
	if (state == 1 || state == 2)
		return true;
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

//lexcial analysis
void lexer(vector<string> &r, string input)
{
	//go to special case if not match common case
	if (isdigit(input[0]))
	{
		if (isInteger(input))
			r.push_back("\nToken: integer\t\tLexer: " + input);
		else if (isReal(input))
			r.push_back("\nToken: real\t\tLexer: " + input);
		else
			r.push_back("\nToken: illegal\t\tLexer: " + input);
	}
	else if (isalpha(input[0]))
	{
		if (isKeyword(input))
			r.push_back("\nToken: keyword\t\tLexer: " + input);
		else if (isIdentifier(input))
			r.push_back("\nToken: identifier\tLexer: " + input);
		else
			r.push_back("\nToken: illegal\t\tLexer: " + input);
	}
	else
	{
		if (isSeparator(input))
			r.push_back("\nToken: separator\tLexer: " + input);
		else if (isOperator(input))
			r.push_back("\nToken: operator\t\tLexer: " + input);
		else
			r.push_back("\nToken: illegal\t\tLexer: " + input);
	}
}

void separateConnectedTokens(vector<string> &t, string input)
{
	//point to last symbol
	int last = 0;
	string tem = "";
	//string after last symbol
	string after;
	//switch to check if the string before the symbol is invaliad
	bool swi = true;
	//conter to avoid checking a connected symbol twice
	int counter = 0;

	for (int i = 0; i < input.length(); ++i)
	{
		//the content is not alnum
		if (!isalnum(input[i]) && input[i] != '.')
		{
			if (counter == 0)
			{
				string te = input.substr(i, 2);
				//two byte token
				if (isTwo(te))
				{
					if (isOperator(te))
					{
						//the token is first of the string
						if (i == 0)
						{
							t.push_back(te);
							last += 2;
						}
						//string before the symbol may not invaliad
						else if (swi)
						{
							after = input.substr(last, i - last);
							if (isKeyword(after))
								t.push_back(after);
							else if (isIdentifier(after))
								t.push_back(after);
							else if (isInteger(after))
								t.push_back(after);
							else if (isReal(after))
								t.push_back(after);
							else
								t.push_back(after);
							t.push_back(te);
						}
						//string before the symbol is invaliad
						else
						{
							after = input.substr(last, i - last);
							t.push_back(after);
							t.push_back(te);
						}
						last = i + 2;
					}

					counter = 2;
				}
				//single byte symbol, basically same as above
				else
				{
					string te = input.substr(i, 1);
					if (isOperator(te))
					{
						if (i == 0)
						{
							t.push_back(te);
							last += 1;
						}
						else if (swi)
						{
							after = input.substr(last, i - last);
							if (isKeyword(after))
								t.push_back(after);
							else if (isIdentifier(after))
								t.push_back(after);
							else if (isInteger(after))
								t.push_back(after);
							else if (isReal(after))
								t.push_back(after);
							else
								t.push_back(after);
							t.push_back(te);
						}
						else
						{
							after = input.substr(last, i - last);
							t.push_back(after);
							t.push_back(te);
						}
						last = i + 1;
					}
					else if (isSeparator(te))
					{
						if (i == 0)
						{
							t.push_back(te);
							last += 1;
						}
						else if (swi)
						{
							after = input.substr(last, i - last);
							if (isKeyword(after))
								t.push_back(after);
							else if (isIdentifier(after))
								t.push_back(after);
							else if (isInteger(after))
								t.push_back(after);
							else if (isReal(after))
								t.push_back(after);
							else
								t.push_back(after);
							t.push_back(te);
						}
						else
						{
							after = input.substr(last, i - last);
							t.push_back(after);
							t.push_back(te);
						}
						last = i + 1;
					}
					else
						swi = false;
				}
			}
			else
				counter--;
		}
	}
	//check string after last symbol
	if (last != input.length())
	{
		after = input.substr(last, input.length() - last);
		if (isKeyword(after))
			t.push_back(after);
		else if (isIdentifier(after))
			t.push_back(after);
		else if (isInteger(after))
			t.push_back(after);
		else if (isReal(after))
			t.push_back(after);
		else
			t.push_back(after);
	}
}

void stringsSeparator(vector<string> v, vector<string> &t)
{
	for (int a = 0; a < v.size(); a++)
	{
		string input = v.at(a);
		string::const_iterator fir = input.begin();
		//go to special case if not match common case
		if (isdigit(*fir))
		{
			if (isInteger(input))
				t.push_back(input);
			else if (isReal(input))
				t.push_back(input);
			else
				separateConnectedTokens(t, input);
		}
		else if (isalpha(*fir))
		{
			if (isKeyword(input))
				t.push_back(input);
			else if (isIdentifier(input))
				t.push_back(input);
			else
				separateConnectedTokens(t, input);
		}
		else
		{
			if (isSeparator(input))
				t.push_back(input);
			else if (isOperator(input))
				t.push_back(input);
			else
				separateConnectedTokens(t, input);
		}
	}
}

void deleteSpace(vector<string> &t)
{
	int i = 0;
	while (i < t.size())
	{
		if (t.at(i) == "")
			t.erase(t.begin() + i);
		else
			++i;
	}
}