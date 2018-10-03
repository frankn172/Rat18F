#pragma once
#include<iostream>
#include<string>
using namespace std;

bool l(char input) {
	if ((input >= 'a'&&input <= 'z') || (input >= 'A'&&input <= 'Z')) {
		return true;
	}
	else return false;
}

bool d(char input) {
	if (input >= '0' && input <= '9') {
		return true;
	}
	else return false;
}

bool dot(char input) {
	if (input == '.') {
		return true;
	}
	else return false;
}

class Identifier{
private:
	string Iden;
public:
	friend class Keywards;
	friend class Operators;
	friend class Seprators;



};

class Keywards {
	bool IsKeyword(string input) {
		string keywards[15] = {"function","int","boolean","real","if","ifend","else","return","put","get","while","whileend","true","false",""};
		for (int i = 0; i < 15; i++) {
			if (input == keywards[i]) {
				return true;
			}
			return false;
		}
	}
};

class Operators {
	bool IsOperator(string input) {
		string operators[11] = { "=","+","-","*","/","==","^=",">","<","=>","=<"};
		for (int i = 0; i < 11; i++) {
			if (input == operators[i]) {
				return true;
			}
			return false;
		}
	}
};

class Separators {
	bool IsSeparator(string input) {
		string separators[9] = { "<",">",":","$$",",",";","(",")","|" };
		for (int i = 0; i < 9; i++) {
			if (input == separators[i]) {
				return true;
			}
			return false;
		}
	}
};

class Integer {

};

class Real {

};

string lexer()
{

}
