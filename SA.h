//CPSC 323
//Compiler Project
//Frank Ngo & Yifei Feng
//SA.h

#pragma once
#include<string>
using namespace std;

string save;
int addr;
string token;
vector<string> t;
vector<string> v;
vector<int> l;
int i = 0;
int op;
bool swit = false;

bool Rat18F();//1
bool Opt_Function_Definitions();//2
bool Qualifier(); //8
bool Opt_Declaration_List();//10
bool Declaration_List();//11
bool Declaration();//12
bool IDs();//13
bool Statement_List();//14
bool Statement();//15
bool Compound();//16 same as body
bool Assign();//17
bool If();//18
bool Return();//19
bool Print();//20
bool Scan();//21
bool While();//22
bool Condition();//23
bool Relop();//24
bool Expression1();//25.1
bool Expression2();//25.2
bool Term1();//26.1
bool Term2();//26.2
bool Factor();//27
bool Primary();//28
bool Empty();//29

			 //receive vectors from main
void passVector1(vector<string> &to, vector<int> &tl)
{
	t = to;
	l = tl;
}
//pass vectors to main
void passVector2(vector<string> &ou)
{
	ou = v;
}

string getToken()
{
	if (i < t.size())
	{
		string temp = t[i];
		i++;
		return temp;
	}
	else
		return " ";
}

bool Rat18F()
{
	if (Opt_Function_Definitions())
	{
		token = getToken();
		if (token == "$$")
		{
			lexer(v, token);
			if (Opt_Declaration_List())
			{
				if (Statement_List())
				{
					token = getToken();
					if (token == "$$")
					{
						lexer(v, token);
						v.push_back("\t<Rat18F> -> <Opt Function Definitions> $$ <Opt Declaration List> <Statement List> $$");
					}
					else
					{
						lexer(v, token);
						v.push_back("\tline " + to_string(l[i]) + "; ' " + token + " ' error, '$$' expected");
						return false;
					}
				}
				else
					return false;
			}
			else
				return false;
		}
		else
		{
			lexer(v, token);
			v.push_back("\tline " + to_string(l[i]) + "; ' " + token + " ' error, '$$' expected");
			return false;
		}
	}
	else
		return false;
	return true;
}

bool Opt_Function_Definitions()
{
	if (Empty())
		v.push_back("\t<Opt Function Definitions> -> <Empty>");
	else
		return false;
	return true;
}

bool Qualifier()
{
	token = getToken();
	if (token == "int")
	{
		lexer(v, token);
		v.push_back("\t<Qualifier> -> int");
	}
	else if (token == "boolean")
	{
		lexer(v, token);
		v.push_back("\t<Qualifier> -> boolean");
	}
	else
	{
		lexer(v, token);
		v.push_back("\tline " + to_string(l[i]) + "; ' " + token + " ' error, 'int', 'boolean' expected");
		return false;
	}
	return true;
}

bool Opt_Declaration_List()
{
	if (t[i] == "int" || t[i] == "boolean")
	{
		if (Declaration_List())
			v.push_back("\t<Opt Declaration List> -> <Declaration List>");
		else
			return false;
	}
	else if (Empty())
		v.push_back("\t<Opt Declaration List> -> <Empty>");
	else
		return false;
	return true;
}

bool Declaration_List()
{
	if (t[i] == "int" || t[i] == "boolean")
	{
		if (Declaration())
		{
			token = getToken();
			if (token == ";")
			{
				lexer(v, token);
				if (Declaration_List())
					v.push_back("\t<Declaration List> -> <Declaration> ; <Declaration List>");
				else
					v.push_back("\t<Declaration List> -> <Declaration>;");
			}
			else
			{
				lexer(v, token);
				v.push_back("\tline " + to_string(l[i]) + "; ' " + token + " ' error, ';' expected");
				return false;
			}
		}
		else
			return false;
	}
	else
		return false;
	return true;
}

bool Declaration()
{
	if (Qualifier())
	{
		if (IDs())
			v.push_back("\t<Declaration> -> <Qualifier > <IDs>");
		else
			return false;
	}
	else
		return false;
	return true;
}

bool IDs()
{
	save = token;
	token = getToken();
	if (isIdentifier(token))
	{
		if (swit) {
			token = "-" + token;
			swit = false;
		}
		//bool or int
		if (save == "boolean") {
			add_bool(token);
		}
		else {
			add_var(token);
		}
		lexer(v, token);
		if (t[i] == ",")
		{
			token = getToken();
			lexer(v, token);
			if (isIdentifier(t[i]))
			{
				if (IDs())
					v.push_back("\t<IDs> -> <Identifier>, <IDs>");
				else
					return false;
			}
			else
				return false;
		}
		else
			v.push_back("\t<IDs> -> <Identifier>");
	}
	else
	{
		lexer(v, token);
		v.push_back("\tline " + to_string(l[i]) + "; ' " + token + " ' error, identifier expected");
		return false;
	}
	return true;
}

bool Statement_List()
{
	if (Statement())
	{
		if (t[i] == "{" || t[i] == "if" || t[i] == "return" || t[i] == "put" || t[i] == "get" || t[i] == "while" || isIdentifier(t[i]))
		{
			if (Statement_List())
				v.push_back("\t<Statement List> -> <Statement> <Statement List>");
			else
				return false;
		}
		else
			v.push_back("\t<Statement List> -> <Statement>");
	}
	else
		return false;
	return true;
}

bool Statement()
{
	if (t[i] == "{")
	{
		if (Compound())
			v.push_back("\t<Statement> -> <Compound>");
		else
			return false;
	}
	else if (t[i] == "if")
	{
		if (If())
			v.push_back("\t<Statement> -> <If>");
		else return false;
	}
	else if (t[i] == "return")
	{
		if (Return())
			v.push_back("\t<Statement> -> <Return>");
		else return false;
	}
	else if (t[i] == "put")
	{
		if (Print())
			v.push_back("\t<Statement> -> <Print>");
		else return false;
	}
	else if (t[i] == "get")
	{
		if (Scan())
			v.push_back("\t<Statement> -> <Scan>");
		else return false;
	}
	else if (t[i] == "while")
	{
		if (While())
			v.push_back("\t<Statement> -> <While>");
		else return false;
	}
	else if (isIdentifier(t[i]))
	{
		if (Assign())
			v.push_back("\t<Statement> -> <Assign>");
		else return false;
	}
	else
	{
		lexer(v, token);
		v.push_back("\tline " + to_string(l[i]) + "; ' " + token + " ' error, '{ <Statement List> }', '<Identifier> = <Expression> ;' ,'if ( <Condition> ) <Statement> ifend | if (<Condition>) <Statement> else <Statement> ifend ', 'return; | return <Expression>;', 'put ( <Expression>);', 'get ( <IDs> );', 'while ( <Condition> ) <Statement> whileend' expected");
		return false;
	}
	return true;
}

bool Compound()
{
	token = getToken();
	if (token == "{")
	{
		lexer(v, token);
		if (Statement_List())
		{
			token = getToken();
			if (token == "}")
			{
				lexer(v, token);
				v.push_back("\t<Compound> -> { < Statement List> }");
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
	return true;
}

bool Assign()
{
	token = getToken();
	if (isIdentifier(token))
	{
		save = token;
		add_var(token);
		lexer(v, token);
		token = getToken();
		if (token == "=")
		{
			lexer(v, token);
			if (Expression1())
			{
				get_instr("POPM", get_address(save));
				token = getToken();
				if (token == ";")
				{
					lexer(v, token);
					v.push_back("\t<Assign> -> <Identifier> = <Expression1>;");
				}
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
	return true;
}

bool If()
{
	token = getToken();
	//1
	if (token == "if")
	{
		addr = address();
		lexer(v, token);
		//2
		token = getToken();
		if (token == "(")
		{
			lexer(v, token);
			//3
			if (Condition())
			{
				//4
				token = getToken();
				if (token == ")")
				{
					lexer(v, token);
					//5
					if (Statement())
					{
						//6
						back_patch(address());
						token = getToken();
						if (token == "else")
						{
							lexer(v, token);
							//7
							if (Statement())
							{
								//8
								token = getToken();
								if (token == "ifend")
								{
									lexer(v, token);
									v.push_back("\t<If> -> if ( <Condition>  ) <Statement> else <Statement> ifend");
								}
								//8
								else
									return false;
							}
							//7
							else
								return false;
						}
						else if (token == "ifend")
						{
							lexer(v, token);
							v.push_back("\t<If> -> if (<Condition>) <Statement> ifend");
						}
						//6
						else
							return false;
					}
					//5
					else
						return false;
				}
				//4
				else
					return false;
			}
			//3
			else
				return false;
		}
		//2
		else
			return false;
	}
	//1
	else
		return false;
	return true;
}

bool Return()
{
	token = getToken();
	if (token == "return")
	{
		lexer(v, token);
		if (t[i] == ";")
		{
			token = getToken();
			lexer(v, token);
			v.push_back("\t<Return> -> return;");
		}
		else if (Expression1())
		{
			token = getToken();
			if (token == ";")
			{
				lexer(v, token);
				v.push_back("\t<Return> -> return; | return <Expression1>;");
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
	return true;
}

bool Print()
{
	token = getToken();
	if (token == "put")
	{

		lexer(v, token);
		token = getToken();
		if (token == "(")
		{
			lexer(v, token);
			if (Expression1())
			{
				get_instr("STDOUT", NULL);
				token = getToken();
				if (token == ")")
				{
					lexer(v, token);
					token = getToken();
					if (token == ";")
					{
						lexer(v, token);
						v.push_back("\t<Print> -> put ( <Expression1> );");
					}
					else
						return false;
				}
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
	return true;
}

bool Scan()
{
	token = getToken();
	if (token == "get")
	{
		lexer(v, token);
		token = getToken();
		if (token == "(")
		{
			lexer(v, token);
			if (IDs())
			{
				save = token;
				get_instr("STDIN", NULL);
				token = getToken();
				get_instr("POPM", get_address(save));
				if (token == ")")
				{
					lexer(v, token);
					token = getToken();
					if (token == ";")
					{
						lexer(v, token);
						v.push_back("\t<Scan> -> get ( <IDs> );");
					}
					else
						return false;
				}
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
	return true;
}

bool While()
{

	token = getToken();
	if (token == "while")
	{
		addr = address();
		get_instr("LABEL", NULL);
		lexer(v, token);
		token = getToken();
		if (token == "(")
		{
			lexer(v, token);
			if (Condition())
			{
				token = getToken();
				if (token == ")")
				{
					lexer(v, token);
					if (Statement())
					{
						get_instr("JUMP", addr);
						back_patch(address());
						token = getToken();
						if (token == "whileend")
						{
							lexer(v, token);
							v.push_back("\t<While> -> while ( <Condition>  ) <Statement> whileend");
						}
						else
						{
							v.push_back("\tline " + to_string(l[i]) + "; ' " + token + " ' error, 'whileend' expected");
							return false;
						}
					}
					else
						return false;
				}
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
	return true;
}

bool Condition()
{
	if (Expression1())
	{
		if (Relop())
		{
			if (Expression1()) {
				if (op == 1) {
					get_instr("EQU", NULL);
					push_jumpstack(address());
					get_instr("JUMPZ", NULL);
				}
				else if (op == 2) {
					get_instr("NEQ", NULL);
					push_jumpstack(address());
					get_instr("JUMPZ", NULL);
				}
				else if (op == 3) {
					get_instr("GRT", NULL);
					push_jumpstack(address());
					get_instr("JUMPZ", NULL);
				}
				else if (op == 4) {
					get_instr("LES", NULL);
					push_jumpstack(address());
					get_instr("JUMPZ", NULL);
				}
				else if (op == 5) {
					get_instr("GEQ", NULL);
					push_jumpstack(address());
					get_instr("JUMPZ", NULL);
				}
				else if (op == 6) {
					get_instr("LEQ", NULL);
					push_jumpstack(address());
					get_instr("JUMPZ", NULL);
				}
				v.push_back("\t<Condition> -> <Expression1> <Relop> <Expression1>");
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
	return true;
}

bool Relop()
{
	token = getToken();
	if (token == "==")
	{

		op = 1;
		lexer(v, token);
		v.push_back("\t<Relop> -> ==");
	}
	else if (token == "^=")
	{
		op = 2;
		lexer(v, token);
		v.push_back("\t<Relop> -> ^=");
	}
	else if (token == ">")
	{
		op = 3;
		lexer(v, token);
		v.push_back("\t<Relop> -> >");
	}
	else if (token == "<")
	{
		op = 4;
		lexer(v, token);
		v.push_back("\t<Relop> -> <");
	}
	else if (token == "=>")
	{
		op = 5;
		lexer(v, token);
		v.push_back("\t<Relop> -> =>");
	}
	else if (token == "=<")
	{
		op = 6;
		lexer(v, token);
		v.push_back("\t<Relop> -> =<");
	}
	else
	{
		lexer(v, token);
		v.push_back("\tline " + to_string(l[i]) + "; ' " + token + " ' error, '==', '^=', '>', '<', '=>', '=<' expected");
		return false;
	}
	return true;
}

bool Expression1()
{
	if (Term1())
	{
		if (Expression2())
			v.push_back("\t<Expression1> -> <Term2> <Expression2>");
		else
			return false;
	}
	else
		return false;
	return true;
}

bool Expression2()
{
	if (t[i] == "+")
	{
		token = getToken();
		lexer(v, token);
		if (Term1())
		{
			get_instr("ADD", NULL);
			if (Expression2())
				v.push_back("\t<Expression2> -> + <Term2> <Expression2>");
			else
				return false;
		}
		else
			return false;
	}
	else if (t[i] == "-")
	{
		token = getToken();
		lexer(v, token);
		if (Term1())
		{
			get_instr("SUB", NULL);
			if (Expression2())
				v.push_back("\t<Expression2> -> - <Term2> <Expression2>");
			else
				return false;
		}
		else
			return false;
	}
	else if (Empty())
		v.push_back("\t<Expression2> -> <Empty>");
	else
		return false;
	return true;
}

bool Term1()
{
	if (Factor())
	{
		if (Term2())
			v.push_back("\t<Term2> -> <Factor> <Term2>");
		else
			return false;
	}
	else
		return false;
	return true;
}

bool Term2()
{
	if (t[i] == "*")
	{
		token = getToken();
		lexer(v, token);
		if (Factor())
		{
			get_instr("MUL", NULL);
			if (Term2())
				v.push_back("\t<Term2> -> * <Factor> <Term2>");
			else
				return false;
		}
		else
			return false;
	}
	else if (t[i] == "/")
	{
		token = getToken();
		lexer(v, token);
		if (Factor())
		{
			get_instr("DIV", NULL);
			if (Term2())
				v.push_back("\t<Term> -> / <Factor> <Term>");
			else
				return false;
		}
		else
			return false;
	}
	else if (Empty())
		v.push_back("\t<Term2> -> <Empty>");
	else
		return false;
	return true;
}

bool Factor()
{
	if (t[i] == "-")
	{
		token = getToken();
		lexer(v, token);
		swit = true;
		if (Primary()) {
			v.push_back("\t<Factor> -> -<Primary>");
		}
		else
			return false;
	}
	else if (Primary()) {
		v.push_back("\t<Factor> -> <Primary>");
	}
	else
		return false;
	return true;
}

bool Primary()
{
	token = getToken();
	if (token == "true")
	{
		lexer(v, token);
		v.push_back("\t<Primary> -> true");
	}
	else if (token == "false")
	{
		lexer(v, token);
		v.push_back("\t<Primary> -> false");
	}
	else if (isIdentifier(token))
	{
		add_var(token);
		get_instr("PUSHM", get_address(token));
		lexer(v, token);
		if (t[i] == "(")
		{
			token = getToken();
			lexer(v, token);
			if (IDs())
			{
				token = getToken();
				if (token == ")")
				{
					lexer(v, token);
					v.push_back("\t<Primary> -> <Identifier> ( <IDs> )");
				}
				else
				{
					lexer(v, token);
					v.push_back("\tline " + to_string(l[i]) + "; ' " + token + " ' error, ')' expected");
					return false;
				}
			}
			else
				return false;
		}
		else
			v.push_back("\t<Primary> -> <Identifier>");
	}
	else if (isInteger(token))
	{
		get_instr("PUSHI", stoi(token));
		lexer(v, token);
		v.push_back("\t<Primary> -> <Integer>");
	}
	else if (token == "(")
	{
		lexer(v, token);
		if (Expression1())
		{
			token = getToken();
			if (token == ")")
			{
				lexer(v, token);
				v.push_back("\t<Primary> -> ( <Expression> )");
			}
			else
			{
				lexer(v, token);
				v.push_back("\tline " + to_string(l[i]) + "; ' " + token + " ' error, ')' expected");
				return false;
			}
		}
		else
			return false;
	}
	else
	{
		lexer(v, token);
		v.push_back("\tline " + to_string(l[i]) + "; ' " + token + " ' error, 'Identifier', 'Integer', 'Identifier ( <IDs> )', '( <Expression> )', 'true', 'false' expected");
		return false;
	}
	return true;
}

bool Empty()
{
	v.push_back("\t<Empty> ->");
	return true;
}