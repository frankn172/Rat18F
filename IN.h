#pragma once

#include<string>
#include<vector>
#include<stack>

using namespace std;

struct symbol {
	string name;
	int Madd;
	string type;
};

struct instruction {
	int Iadd;
	string op;
	int ope;
};

struct var {
	int Vadd;
	int n;
};

stack<int> ST;
stack<int> JS;
vector<symbol> S;
vector<instruction> I;
vector<var> M;

int Scounter = 5000;
int Icounter = 1;
int result;

void add_var(string token) {
	bool swi = true;
	for (int i = 0; i < S.size(); i++) {
		if (token == S[i].name) {
			swi = false;
		}
	}
	if (swi) {
		S.push_back({ token,Scounter,"int" });
		Scounter++;
	}
}

int get_address(string token) {
	int temp;
	for (int i = 0; i < S.size(); i++)
	{
		if (token == S[i].name) {
			temp = S[i].Madd;
		}
	}
	return temp;
}

int address() {
	return Icounter;
}

void push_jumpstack(int add) {
	JS.push(add);
}

void get_instr(string op, int oprnd) {
	I.push_back({ Icounter,op,oprnd });
	Icounter++;
}

void back_patch(int jump_addr) {
	int addr = JS.top();
	JS.pop();
	I[addr].ope = jump_addr;
}
