//CPSC 323
//Compiler Project
//Frank Ngo & Yifei Feng
//IN.h

#pragma once

#include<string>
#include<vector>
#include<stack>
using namespace std;

//symbol table struct
struct symbol
{
	string name;
	int Madd;
	string type;
};

//instruction table struct
struct instruction
{
	int Iadd;
	string op;
	int ope;
};

//stack of operation
stack<int> ST;
//jump stack
stack<int> JS;
//symbol table
vector<symbol> S;
//instruction table
vector<instruction> I;
//symbol address counter
int Scounter = 5000;
//instruction address counter
int Icounter = 1;

//add int type into symbol table
void add_var(string token)
{
	bool swi = true;
	for (int i = 0; i < S.size(); i++)
	{
		if (token == S[i].name&&S[i].type == "int")
			swi = false;
	}
	if (swi)
	{
		S.push_back({ token,Scounter,"int" });
		Scounter++;
	}
}
//add bool type into symbol table
void add_bool(string token)
{
	bool swi = true;
	for (int i = 0; i < S.size(); i++)
	{
		if (token == S[i].name&&S[i].type == "boolean")
			swi = false;
	}
	if (swi)
	{
		S.push_back({ token,Scounter,"bollean" });
		Scounter++;
	}
}
//get address of symbol
int get_address(string token)
{
	int temp;
	for (int i = 0; i < S.size(); i++)
	{
		if (token == S[i].name)
			temp = S[i].Madd;
	}
	return temp;
}

//get address of instruction
int address()
{
	return Icounter;
}

//add jump address
void push_jumpstack(int add)
{
	JS.push(add);
}

//generate instruction
void get_instr(string op, int oprnd)
{
	I.push_back({ Icounter,op,oprnd });
	Icounter++;
}

//go back to add address of jump
void back_patch(int jump_addr)
{
	int addr = JS.top() - 1;
	JS.pop();
	I[addr].ope = jump_addr;
}