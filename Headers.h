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
	string::const_iterator it = input.begin();
	while ((it != input.end()) && (isdigit(*it)))
	{
		++it;
	}
	return ((!input.empty()) && (it == input.end()));
}

bool isReal(string input)
{
	int dot = input.find('.');
	if (dot != -1)
	{
		for (int i = 0; i < dot; ++i)
		{
			if (!isdigit(input[i]))
				return false;
		}
		for (int j = dot + 1; j < input.length(); ++j)
		{
			if (!isdigit(input[j]))
				return false;
		}
		return true;
	}
	else return false;
}

bool isIdentifier(string input)
{
	int len = input.length();
	if (len == 1)
		return (isalpha(input[0]));
	else if ((!isalpha(input[0])) || (!isalpha(input[len - 1])))
		return false;
	else
	{
		for (int i = 1; i < len - 1; ++i)
		{
			if (!isalnum(input[i]))
				return false;
		}
		return true;
	}
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

//separate string
string sep(string input)
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
							tem = tem + "operator\t" + te + "\n";
							last += 2;
						}
						//string before the symbol may not invaliad
						else if (swi)
						{
							after = input.substr(last, i - last);
							if (isKeyword(after))
								tem = tem + "keyword\t\t" + after + "\n";
							else if (isIdentifier(after))
								tem = tem + "identifier\t" + after + "\n";
							else if (isInteger(after))
								tem = tem + "integer\t\t" + after + "\n";
							else if (isReal(after))
								tem = tem + "real\t\t" + after + "\n";
							else
								tem = tem + after;
							tem = tem + "operator\t" + te + "\n";
						}
						//string before the symbol is invaliad
						else
						{
							after = input.substr(last, i - last);
							tem = tem + "\t\t" + after + "\n";
							tem = tem + "operator\t" + te + "\n";
						}
						last = i + 2;
					}
					//same as OP
					else if (isSeparator(te))
					{
						if (i == 0)
						{
							tem = tem + "separator\t" + te + "\n";
							last += 1;
						}
						else if (swi)
						{
							after = input.substr(last, i - last);
							if (isKeyword(after))
								tem = tem + "keyword\t\t" + after + "\n";
							else if (isIdentifier(after))
								tem = tem + "identifier\t" + after + "\n";
							else if (isInteger(after))
								tem = tem + "integer\t\t" + after + "\n";
							else if (isReal(after))
								tem = tem + "real\t\t" + after + "\n";
							else
								tem = tem + after;
							tem = tem + "separator\t" + te + "\n";
						}
						else
						{
							after = input.substr(last, i - last);
							tem = tem + "\t\t" + after + "\n";
							tem = tem + "separator\t" + te + "\n";
						}
						last = i + 2;
					}
					counter = 2;
				}
				//single byte symbol, basically same as above
				else
				{
					string t = input.substr(i, 1);
					if (isOperator(t))
					{
						if (i == 0)
						{
							tem = tem + "operator\t" + t + "\n";
							last += 1;
						}
						else if (swi)
						{
							after = input.substr(last, i - last);
							if (isKeyword(after))
								tem = tem + "keyword\t\t" + after + "\n";
							else if (isIdentifier(after))
								tem = tem + "identifier\t" + after + "\n";
							else if (isInteger(after))
								tem = tem + "integer\t\t" + after + "\n";
							else if (isReal(after))
								tem = tem + "real\t\t" + after + "\n";
							else
								tem = tem + after;
							tem = tem + "operator\t" + t + "\n";
						}
						else
						{
							after = input.substr(last, i - last);
							tem = tem + "\t\t" + after + "\n";
							tem = tem + "operator\t" + t + "\n";
						}
						last = i + 1;
					}
					else if (isSeparator(t))
					{
						if (i == 0)
						{
							tem = tem + "separator\t" + t + "\n";
							last += 1;
						}
						else if (swi)
						{
							after = input.substr(last, i - last);
							if (isKeyword(after))
								tem = tem + "keyword\t\t" + after + "\n";
							else if (isIdentifier(after))
								tem = tem + "identifier\t" + after + "\n";
							else if (isInteger(after))
								tem = tem + "integer\t\t" + after + "\n";
							else if (isReal(after))
								tem = tem + "real\t\t" + after + "\n";
							else
								tem = tem + after;
							tem = tem + "separator\t" + t + "\n";
						}
						else
						{
							after = input.substr(last, i - last);
							tem = tem + "\t\t" + after + "\n";
							tem = tem + "separator\t" + t + "\n";
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
			tem = tem + "keyword\t\t" + after + "\n";
		else if (isIdentifier(after))
			tem = tem + "identifier\t" + after + "\n";
		else if (isInteger(after))
			tem = tem + "integer\t\t" + after + "\n";
		else if (isReal(after))
			tem = tem + "real\t\t" + after + "\n";
		else
			tem = tem + "\t\t" + after + "\n";
	}
	//delete last \n to avoid blanks 
	if (tem != "")
		tem = tem.substr(0, tem.length() - 1);
	return tem;
}

string lexer(string input)
{
	string::const_iterator fir = input.begin();
	//go to special case if not match common case
	if (isdigit(*fir))
	{
		if (isInteger(input))
			return ("integer\t\t" + input);
		else if (isReal(input))
			return ("real\t\t" + input);
		else return sep(input);
	}
	else if (isalpha(*fir))
	{
		if (isKeyword(input))
			return ("keyword\t\t" + input);
		else if (isIdentifier(input))
			return ("identifier\t" + input);
		else return sep(input);
	}
	else
	{
		if (isSeparator(input))
			return ("separator\t" + input);
		else if (isOperator(input))
			return ("operator\t" + input);
		else return sep(input);
	}
}