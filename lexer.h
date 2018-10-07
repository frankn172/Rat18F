#pragma once
#include<iostream>
#include<string>
#include<vector>
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
	string separators[9] = { ":","$$",",",";","(",")","|","{","}" };
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
	{
		++it;
	}
	return ((!input.empty()) && (it == input.end()));
}

bool isReal(string input)
{/*
	int dot = input.find('.');
	if (dot != -1)
	{
		for (int i = 0; i < dot; i++)
		{
			if (!isdigit(input[i]))
				return false;
		}
		for (int j = dot; j < input.length(); j++)
		{
			if (!isdigit(input[j]))
				return false;
		}
		return true;
	}
	else return false;*/
	string before = input.substr(0, input.find("."));
	string after = input.substr(input.find(".") + 1, input.size() + 1);
	return ((isInteger(before)) && (isInteger(after)));
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
		for (int i = 1; i < len -1; i++)
		{
			if (!isalnum(input[i]))
				return false;
		}
		return true;
	}
}

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

string lexer(string input)
{
	string::const_iterator fir = input.begin();
	if (isdigit(*fir))
	{
		if (isInteger(input))
			return ("integer\t\t" + input);
		else if (isReal(input))
			return ("real\t\t" + input);
		else return input;
	}

	else if (isalpha(*fir))
	{
		if (isKeyword(input))
			return ("keyword\t\t" + input);
		else if (isIdentifier(input))
			return ("identifier\t" + input);
		else return input;
	}

	else
	{
		if (isSeparator(input))
			return ("separator\t" + input);
		else if (isOperator(input))
			return ("operator\t" + input);
		else return input;
	}
}
