#pragma once
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
	string separators[7] = { ":","$$",",",";","(",")","|" };
	for (int i = 0; i < 7; i++)
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
	string delimiter = ".";
	string before = input.substr(0, input.find(delimiter));
	string after = input.substr(input.find(delimiter) + 1, input.size() + 1);
	return ((isInteger(before)) && (isInteger(after)));
}

bool isIdentifier(string input) {
	int len = input.length();
	if (len == 1) {
		return true;
	}
	for (int i = 0; i < len; i++) {
		if (!isdigit(input[i]) || !isalpha(input[i])) {
			return false;
		}
	}
	if (!isalpha(input[len - 1])) {
		return false;
	}
	return true;
}

bool CM = true;
void isComment(string input) {
	if (input == "[*") {
		CM = false;
	}
	if (input == "*]") {
		CM = true;
	}
}

string lexer(string input)
{
	string::const_iterator fir = input.begin();
	if (CM) {
		if (isdigit(*fir)) {
			if (isInteger(input)) {
				return ("integer\t\t" + input);
			}
			if (isReal(input)) {
				return ("real\t\t" + input);
			}
		}

		else if (isalpha(*fir)) {
			if (isKeyword(input)) {
				return ("keyword\t\t" + input);
			}
			if (isIdentifier(input)) {
				return ("identifier\t" + input);
			}
		}

		else {
			if (isSeparator(input)) {
				return ("separator\t" + input);
			}
			if (isOperator(input)) {
				return ("operator\t" + input);
			}
		}
	}
}
