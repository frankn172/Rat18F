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

bool istwo(string input) {
	string temp = input;
	string twocase[5] = {"==","^=","=<","=>","$$"};
	for (int i = 0; i < 5; i++) {
		if (temp == twocase[i]) {
			return true;
		}
		else return false;
	}
}

string sep(string input)
{
	int last = 0;
	string tem = "";
	string after;
	bool swi = true;
	int counter=0;
	for (int i = 0; i < input.length(); ++i)
	{
		if (!isalnum(input[i]) && input[i] != '.')
		{
			if (counter == 0) {
				string te = input.substr(i, 2);
				if(istwo(te)){
					if (isOperator(te))
					{
						if (i == 0)
						{
							tem = tem + "operator\t" + te + "\n";
							last += 2;
						}
						else if (swi)
						{
							after = input.substr(last, i - last);
							if (isIdentifier(after))
								tem = tem + "identifier\t" + after + "\n";
							else if (isKeyword(after))
								tem = tem + "keyword\t\t" + after + "\n";
							else if (isInteger(after))
								tem = tem + "integer\t\t" + after + "\n";
							else if (isReal(after))
								tem = tem + "real\t\t" + after + "\n";
							else
								tem = tem + after;
							tem = tem + "operator\t" + te+ "\n";
						}
						else
						{
							after = input.substr(last, i - last);
							tem = tem + "\t\t" +after + "\n";
							tem = tem + "operator\t" + te + "\n";
						}
						last = i + 2;
					}
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
							if (isIdentifier(after))
								tem = tem + "identifier\t" + after + "\n";
							else if (isKeyword(after))
								tem = tem + "keyword\t\t" + after + "\n";
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
				else {
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
						if (isIdentifier(after))
							tem = tem + "identifier\t" + after + "\n";
						else if (isKeyword(after))
							tem = tem + "keyword\t\t" + after + "\n";
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
						if (isIdentifier(after))
							tem = tem + "identifier\t" + after + "\n";
						else if (isKeyword(after))
							tem = tem + "keyword\t\t" + after + "\n";
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
			else{
			counter--;
			}
		}
	}
	if (last != input.length())
	{
		after = input.substr(last, input.length() - last);
		if (isIdentifier(after))
			tem = tem + "identifier\t" + after+"\n";
		else if (isKeyword(after))
			tem = tem + "keyword\t\t" + after + "\n";
		else if (isInteger(after))
			tem = tem + "integer\t\t" + after + "\n";
		else if (isReal(after))
			tem = tem + "real\t\t" + after + "\n";
		else
			tem = tem +"\t\t"+ after + "\n";
	}
	if (tem != "") {
		tem = tem.substr(0, tem.length() - 1);
	}
	return tem;
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
