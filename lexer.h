#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;

vector<string> v;

struct node {
	int num;
	node* next;
};


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
{
	int dot = input.find('.');
	if (dot != -1)
	{
		for (int i = 0; i < dot; i++)
		{
			if (!isdigit(input[i]))
				return false;
		}
		for (int j = dot+1; j < input.length(); j++)
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
		for (int i = 1; i < len - 1; i++)
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

//separate tokens from a long string
string sep(string input) {
	int last = 0;
	string tem="";
	string after;
	bool swi=true;

	for (int i = 0; i < input.length(); i++) {
		//connected two op/sep
		if (!isalnum(input[i])&& !isalnum(input[i+1])) {
			string t = input.substr(i, 2);
			string ft = input.substr(i, 1);
			string lt = input.substr(1 + 1, 1);
			//op with two digit symbol
			if (isOperator(t)) {
				if (swi) {
					after = input.substr(last, i - last);
					if (isIdentifier(after)) {
						tem = tem + "identifier\t" + after + "\n";
					}
					else if (isKeyword(after)) {
						tem = tem + "keyword\t\t" + after + "\n";
					}
					else if (isInteger(after)) {
						tem = tem + "integer\t\t" + after + "\n";
					}
					else if (isReal(after)) {
						tem = tem + "real\t" + after + "\n";
					}
					else {
						tem = tem + after + "\n";
					}
					tem = tem + "operator\t" + t + "\n";
				}
				else {
					after = input.substr(last, i - last);
					tem = tem + after + "\n";
					tem = tem + "operator\t" + t + "\n";
				}
				last = i + 2;
			}
			//sep with two digit sybol
			else if (isSeparator(t)) {
				if (swi) {
					after = input.substr(last, i - last);
					if (isIdentifier(after)) {
						tem = tem + "identifier\t" + after + "\n";
					}
					else if (isKeyword(after)) {
						tem = tem + "keyword\t\t" + after + "\n";
					}
					else if (isInteger(after)) {
						tem = tem + "integer\t\t" + after + "\n";
					}
					else if (isReal(after)) {
						tem = tem + "real\t" + after + "\n";
					}
					else {
						tem = tem + after + "\n";
					}
					tem = tem + "separator\t" + t + "\n";
				}
				else {
					after = input.substr(last, i - last);
					tem = tem + after + "\n";
					tem = tem + "separator\t" + t + "\n";
				}
				last = i + 2;
			} 
			//connected one digit symbol and first one is op
			else if (isOperator(ft)) {
				if (swi) {
					after = input.substr(last, i - last);
					if (isIdentifier(after)) {
						tem = tem + "identifier\t" + after + "\n";
					}
					else if (isKeyword(after)) {
						tem = tem + "keyword\t\t" + after + "\n";
					}
					else if (isInteger(after)) {
						tem = tem + "integer\t\t" + after + "\n";
					}
					else if (isReal(after)) {
						tem = tem + "real\t" + after + "\n";
					}
					else {
						tem = tem + after + "\n";
					}
					tem = tem + "operator\t" + ft + "\n";
				}
				else {
					after = input.substr(last, i - last);
					tem = tem + after + "\n";
					tem = tem + "operator\t" + ft + "\n";
				}

				if (isSeparator(lt)) {
					tem = tem + "separator\t" + lt + "\n";
					last = i + 1;
				}
				else if (isOperator(lt)) {
					tem = tem + "operator\t" + lt + "\n";
					last = i + 1;
				}
				else {
					swi = false;
				}
				last = i + 1;
			}
			//connected one digit symbol, first is sep
			else if (isSeparator(ft)) {
				if (swi) {
					after = input.substr(last, i - last);
					if (isIdentifier(after)) {
						tem = tem + "identifier\t" + after + "\n";
					}
					else if (isKeyword(after)) {
						tem = tem + "keyword\t\t" + after + "\n";
					}
					else if (isInteger(after)) {
						tem = tem + "integer\t\t" + after + "\n";
					}
					else if (isReal(after)) {
						tem = tem + "real\t" + after + "\n";
					}
					else {
						tem = tem + after + "\n";
					}
					tem = tem + "sepaprator\t" + ft + "\n";
				}
				else {
					after = input.substr(last, i - last);
					tem = tem + after + "\n";
					tem = tem + "operator\t" + ft + "\n";
				}

				if (isOperator(lt)) {
					tem = tem + "operator\t" + lt + "\n";
					last = i + 1;
				}
				else if (isSeparator(lt)) {
					tem = tem + "separator\t" + lt + "\n";
					last = i + 1;
				}
				else {
					swi = false;
				}
				last = i + 1;
			}
			else {
				swi = false;
			}
		}
		//first one is op/sep
		else if (i == 0 && !isalnum(input[i])) {
			string t = input.substr(0, 1);
			if (isOperator(t)) {
				tem = tem + "operator\t" + t + "\n";
				last += 1;
			}
			else if (isSeparator(t)) {
				tem = tem + "separator\t" + t + "\n";
				last += 1;
			}
			last = 1;
		}
		//just one op/sep
		else if (!isalnum(input[i])&&isalnum(input[i-1])&&input[i]!='.') {
			string t = input.substr(i,1);
			if (isOperator(t) ) {
				if (swi) {
					after = input.substr(last, i - last);
					if (isIdentifier(after)) {
						tem = tem + "identifier\t" + after + "\n";
					}
					else if (isKeyword(after)){
						tem = tem +"keyword\t\t" + after + "\n";
					}
					else if (isInteger(after)) {
						tem = tem + "integer\t\t" + after + "\n";
					}
					else if (isReal(after)) {
						tem = tem + "real\t\t" + after + "\n";
						}
					else {
						tem = tem + after + "\n";
					}
					tem = tem + "operator\t" + t + "\n";
				}
				else {
					after = input.substr(last, i - last);
					tem = tem + after + "\n";
					tem = tem + "operator\t" + t + "\n";
				}
				last = i+1;
			}
			else if (isSeparator(t)) {
				if (swi) {
					after = input.substr(last, i - last);
					if (isIdentifier(after)) {
						tem = tem + "identifier\t" + after + "\n";
					}
					else if (isKeyword(after)) {
						tem = tem + "keyword\t\t" + after + "\n";
					}
					else if (isInteger(after)) {
						tem = tem + "integer\t\t" + after + "\n";
					}
					else if (isReal(after)) {
						tem = tem + "real\t\t" + after + "\n";
					}
					else {
						tem = tem + after + "\n";
					}
					tem = tem + "separator\t" + t + "\n";
				}
				else {
					after = input.substr(last, i - last);
					tem = tem + after + "\n";
					tem = tem + "separator\t" + t + "\n";
				}
				last = i+1;
			}
			else {
				swi = false;
			}
		}
	}
	if (last == 1) {
			after = input.substr(last, input.length());
			if (isIdentifier(after)) {
				tem = tem + "identifier\t" + after + "\n";
			}
			else if (isKeyword(after)) {
				tem = tem + "keyword\t\t" + after + "\n";
			}
			else if (isInteger(after)) {
				tem = tem + "integer\t\t" + after + "\n";
			}
			else if (isReal(after)) {
				tem = tem + "real\t\t" + after + "\n";
			}
			else {
				tem = tem + after + "\n";
			}
		}
	else if (isalnum(input[input.length()-1])) {
		after = input.substr(last, input.length() - last);
		if (isIdentifier(after)) {
			tem = tem + "identifier\t" + after + "\n";
		}
		else if (isKeyword(after)) {
			tem = tem + "keyword\t\t" + after + "\n";
		}
		else if (isInteger(after)) {
			tem = tem + "integer\t\t" + after + "\n";
		}
		else if (isReal(after)) {
			tem = tem + "real\t\t" + after + "\n";
		}
		else {
			tem = tem + after + "\n";
		}
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
