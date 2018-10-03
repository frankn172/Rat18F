#include<iostream>
#include<string>
using namespace std;

bool l(char input)
{
	return ((toupper(input) >= 'A') && (toupper(input) <= 'Z'));
}

bool d(char input)
{
	return ((input >= 0) && (input <= 9));
}

bool dot(char input)
{
	return (input == '.');
}

class Identifier
{
private:
	string Iden;
public:
	friend class Keywords;
	friend class Operators;
	friend class Seprators;
	friend class Integer;
	friend class Real;
};

class Keywords
{
	bool isKeyword(string input)
	{
		string keywords[15] = { "function","int","boolean","real","if","ifend","else","return","put","get","while","whileend","true","false","" };
		for (int i = 0; i < 15; i++)
		{
			if (input.compare(keywords[i]) == 0)
				return true;
		}
		return false;
	}
};

class Operators
{
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
};

class Separators
{
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
};

class Integer
{
	bool isInteger(string input)
	{
		string::const_iterator it = input.begin();
		while ((it != input.end()) && (isdigit(*it)))
			++it;
		return (!input.empty() && it == input.end());
	}
};

class Real {

};