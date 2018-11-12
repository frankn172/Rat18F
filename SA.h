#pragma once
#include<string>
using namespace std;

string token;
vector<string> t;
vector<string> v;
vector<int> l;
int i = 0;

bool Rat18F();//1
bool Opt_Function_Definitions();//2
bool Function_Definitions();//3
bool Function();//4
bool Opt_Parameter_List();//5
bool Parameter_List();//6
bool Parameter();//7
bool Qualifier(); //8
bool Body();//9
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
						v.push_back("<Rat18F> -> <Opt Function Definitions> $$ <Opt Declaration List> <Statement List> $$");
					}
					else
					{
						lexer(v, token);
						v.push_back("line " + to_string(l[i]) + "; ' " + token + " ' error, '$$' expected");
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
			v.push_back("line " + to_string(l[i]) + "; ' " + token + " ' error, '$$' expected");
			return false;
		}
	}
	else
		return false;
	return true;
}

bool Opt_Function_Definitions()
{
	if (t[i] == "function")
	{
		if (Function_Definitions())
			v.push_back("<Opt Function Definitions> -> <Function Definitions>");
		else
			return false;
	}
	else if (Empty())
		v.push_back("<Opt Function Definitions> -> <Empty>");
	else
		return false;
	return true;
}

bool Function_Definitions()
{
	if (t[i] == "function")
	{
		if (Function())
		{
			if (Function_Definitions())
				v.push_back("<Function Definitions> -> <Function> <Function Definitions>");
			else if (Empty())
				v.push_back("<Function Definitions> -> <Function>");
		}
		else
			return false;
	}
	else
		return false;
	return true;
}

bool Function()
{
	token = getToken();
	if (token == "function")
	{
		lexer(v, token);
		token = getToken();
		if (isIdentifier(token))
		{
			lexer(v, token);
			token = getToken();
			if (token == "(")
			{
				lexer(v, token);
				if (Opt_Parameter_List())
				{
					token = getToken();
					if (token == ")")
					{
						lexer(v, token);
						if (Opt_Declaration_List())
						{
							if (Body())
								v.push_back("<Function> -> function <Identifier> ( <Opt Parameter List> ) <Opt Declaration List> <Body>");
							else
								return false;
						}
						else
							return false;
					}
					else
					{
						lexer(v, token);
						v.push_back("line " + to_string(l[i]) + "; ' " + token + " ' error, ')' expected");
						return false;
					}
				}
				else
					return false;
			}
			else
			{
				lexer(v, token);
				v.push_back("line " + to_string(l[i]) + "; ' " + token + " ' error, '(' expected");
				return false;
			}
		}
		else
		{
			lexer(v, token);
			v.push_back("line " + to_string(l[i]) + "; ' " + token + " ' error, Identifier expected");
			return false;
		}
	}
	else
	{
		lexer(v, token);
		v.push_back("line " + to_string(l[i]) + "; ' " + token + " ' error, 'function' expected");
		return false;
	}
	return true;
}

bool Opt_Parameter_List()
{
	if (isIdentifier(t[i]))
	{
		if (Parameter_List())
			v.push_back("<Opt Parameter List> -> <Parameter List>");
		else
			return false;
	}
	else if (Empty())
		v.push_back("<Opt Parameter List> -> <Empty>");
	else
		return false;
	return true;
}

bool Parameter_List()
{
	if (Parameter())
	{
		if (t[i] == ",")
		{
			token = getToken();
			lexer(v, token);
			if (Parameter_List())
				v.push_back("<Parameter List> -> <Parameter> , <Parameter List>");
			else
				return false;
		}
		else
			v.push_back("<Parameter List> -> <Parameter>");
	}
	else
		return false;
	return true;
}

bool Parameter()
{
	if (IDs())
	{
		token = getToken();
		if (token == ":")
		{
			lexer(v, token);
			if (Qualifier())
				v.push_back("<Parameter> -> <IDs > : <Qualifier>");
			else
				return false;
		}
		else
		{
			lexer(v, token);
			v.push_back("line " + to_string(l[i]) + "; ' " + token + " ' error, ':' expected");
			return false;
		}
	}
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
		v.push_back("<Qualifier> -> int");
	}
	else if (token == "boolean")
	{
		lexer(v, token);
		v.push_back("<Qualifier> -> real");
	}
	else if (token == "real")
	{
		lexer(v, token);
		v.push_back("<Qualifier> -> real");
	}
	else
	{
		lexer(v, token);
		v.push_back("line " + to_string(l[i]) + "; ' " + token + " ' error, 'int', 'boolean', 'real' expected");
		return false;
	}
	return true;
}

bool Body()
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
				v.push_back("<Body> -> { < Statement List> }");
			}
			else
			{
				lexer(v, token);
				v.push_back("line " + to_string(l[i]) + "; ' " + token + " ' error, '}' expected");
				return false;
			}
		}
		else
			return false;
	}
	else
	{
		lexer(v, token);
		v.push_back("line " + to_string(l[i]) + "; ' " + token + " ' error, '{' expected");
		return false;
	}
	return true;
}

bool Opt_Declaration_List()
{
	if (t[i] == "int" || t[i] == "boolean" || t[i] == "real")
	{
		if (Declaration_List())
			v.push_back("<Opt Declaration List> -> <Declaration List>");
		else
			return false;
	}
	else if (Empty())
		v.push_back("<Opt Declaration List> -> <Empty>");
	else
		return false;
	return true;
}

bool Declaration_List()
{
	if (t[i] == "int" || t[i] == "boolean" || t[i] == "real")
	{
		if (Declaration())
		{
			token = getToken();
			if (token == ";")
			{
				lexer(v, token);
				if (Declaration_List())
					v.push_back("<Declaration List> -> <Declaration> ; <Declaration List>");
				else
					v.push_back("<Declaration List> -> <Declaration>;");
			}
			else
			{
				lexer(v, token);
				v.push_back("line " + to_string(l[i]) + "; ' " + token + " ' error, ';' expected");
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
			v.push_back("<Declaration> -> <Qualifier > <IDs>");
		else
			return false;
	}
	else
		return false;
	return true;
}

bool IDs()
{
	token = getToken();
	if (isIdentifier(token))
	{
		lexer(v, token);
		if (t[i] == ",")
		{
			token = getToken();
			lexer(v, token);
			if (isIdentifier(t[i]))
			{
				if (IDs())
					v.push_back("<IDs> -> <Identifier>, <IDs>");
				else
					return false;
			}
			else
				return false;
		}
		else
			v.push_back("<IDs> -> <Identifier>");
	}
	else
	{
		lexer(v, token);
		v.push_back("line " + to_string(l[i]) + "; ' " + token + " ' error, identifier expected");
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
				v.push_back("<Statement List> -> <Statement> <Statement List>");
			else
				return false;
		}
		else
			v.push_back("<Statement List> -> <Statement>");
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
			v.push_back("<Statement> -> <Compound>");
		else
			return false;
	}
	else if (t[i] == "if")
	{
		if (If())
			v.push_back("<Statement> -> <If>");
		else return false;
	}
	else if (t[i] == "return")
	{
		if (Return())
			v.push_back("<Statement> -> <Return>");
		else return false;
	}
	else if (t[i] == "put")
	{
		if (Print())
			v.push_back("<Statement> -> <Print>");
		else return false;
	}
	else if (t[i] == "get")
	{
		if (Scan())
			v.push_back("<Statement> -> <Scan>");
		else return false;
	}
	else if (t[i] == "while")
	{
		if (While())
			v.push_back("<Statement> -> <While>");
		else return false;
	}
	else if (isIdentifier(t[i]))
	{
		if (Assign())
			v.push_back("<Statement> -> <Assign>");
		else return false;
	}
	else
	{
		lexer(v, token);
		v.push_back("line " + to_string(l[i]) + "; ' " + token + " ' error, '{ <Statement List> }', '<Identifier> = <Expression> ;' ,'if ( <Condition> ) <Statement> ifend | if (<Condition>) <Statement> else <Statement> ifend ', 'return; | return <Expression>;', 'put ( <Expression>);', 'get ( <IDs> );', 'while ( <Condition> ) <Statement> whileend' expected");
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
				v.push_back("<Compound> -> { < Statement List> }");
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
		lexer(v, token);
		token = getToken();
		if (token == "=")
		{
			lexer(v, token);
			if (Expression1())
			{
				token = getToken();
				if (token == ";")
				{
					lexer(v, token);
					v.push_back("<Assign> -> <Identifier> = <Expression1>;");
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
		lexer(v, token);
		//2
		token = getToken();
		if (token == "(")
		{
			lexer(v, token);
			//3
			token = getToken();
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
									v.push_back("<If> -> if ( <Condition>  ) <Statement> else <Statement> ifend");
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
							v.push_back("<If> -> if (<Condition>) <Statement> ifend");
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
			v.push_back("<Return> -> return;");
		}
		else if (Expression1())
		{
			token = getToken();
			if (token == ";")
			{
				lexer(v, token);
				v.push_back("<Return> -> return; | return <Expression1>;");
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
				token = getToken();
				if (token == ")")
				{
					lexer(v, token);
					token = getToken();
					if (token == ";")
					{
						lexer(v, token);
						v.push_back("<Print> -> put ( <Expression1> );");
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
				token = getToken();
				if (token == ")")
				{
					lexer(v, token);
					token = getToken();
					if (token == ";")
					{
						lexer(v, token);
						v.push_back("<Scan> -> get ( <IDs> );");
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
						token = getToken();
						if (token == "whileend")
						{
							lexer(v, token);
							v.push_back("<While> -> while ( <Condition>  ) <Statement> whileend");
						}
						else
						{
							v.push_back("line " + to_string(l[i]) + "; ' " + token + " ' error, 'whileend' expected");
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
			if (Expression1())
				v.push_back("<Condition> -> <Expression1> <Relop> <Expression1>");
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
		lexer(v, token);
		v.push_back("<Relop> -> ==");
	}
	else if (token == "^=")
	{
		lexer(v, token);
		v.push_back("<Relop> -> ^=");
	}
	else if (token == ">")
	{
		lexer(v, token);
		v.push_back("<Relop> -> >");
	}
	else if (token == "<")
	{
		lexer(v, token);
		v.push_back("<Relop> -> <");
	}
	else if (token == "=>")
	{
		lexer(v, token);
		v.push_back("<Relop> -> =>");
	}
	else if (token == "=<")
	{
		lexer(v, token);
		v.push_back("<Relop> -> =<");
	}
	else
	{
		lexer(v, token);
		v.push_back("line " + to_string(l[i]) + "; ' " + token + " ' error, '==', '^=', '>', '<', '=>', '=<' expected");
		return false;
	}
	return true;
}

bool Expression1()
{
	if (Term1())
	{
		if (Expression2())
			v.push_back("<Expression1> -> <Term2> <Expression2>");
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
			if (Expression2())
				v.push_back("<Expression2> -> + <Term2> <Expression2>");
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
			if (Expression2())
				v.push_back("<Expression2> -> - <Term2> <Expression2>");
			else
				return false;
		}
		else
			return false;
	}
	else if (Empty())
		v.push_back("<Expression2> -> <Empty>");
	else
		return false;
	return true;
}

bool Term1()
{
	if (Factor())
	{
		if (Term2())
			v.push_back("<Term2> -> <Factor> <Term2>");
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
			if (Term2())
				v.push_back("<Term2> -> * <Factor> <Term2>");
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
			if (Term2())
				v.push_back("<Term> -> / <Factor> <Term>");
			else
				return false;
		}
		else
			return false;
	}
	else if (Empty())
		v.push_back("<Term2> -> <Empty>");
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
		if (Primary())
			v.push_back("<Factor> -> -<Primary>");
		else
			return false;
	}
	else if (Primary())
		v.push_back("<Factor> -> <Primary>");
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
		v.push_back("<Primary> -> true");
	}
	else if (token == "false")
	{
		lexer(v, token);
		v.push_back("<Primary> -> false");
	}
	else if (isIdentifier(token))
	{
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
					v.push_back("<Primary> -> <Identifier> ( <IDs> )");
				}
				else
				{
					lexer(v, token);
					v.push_back("line " + to_string(l[i]) + "; ' " + token + " ' error, ')' expected");
					return false;
				}
			}
			else
				return false;
		}
		else
			v.push_back("<Primary> -> <Identifier>");
	}
	else if (isInteger(token))
	{
		lexer(v, token);
		v.push_back("<Primary> -> <Integer>");
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
				v.push_back("<Primary> -> ( <Expression> )");
			}
			else
			{
				lexer(v, token);
				v.push_back("line " + to_string(l[i]) + "; ' " + token + " ' error, ')' expected");
				return false;
			}
		}
		else
			return false;
	}
	else if (isReal(token))
	{
		lexer(v, token);
		v.push_back("<Primary> -> <Real>");
	}

	else
	{
		lexer(v, token);
		v.push_back("line " + to_string(l[i]) + "; ' " + token + " ' error, 'Identifier', 'Integer', 'Identifier ( <IDs> )', '( <Expression> )', 'Real', 'true', 'false' expected");
		return false;
	}
	return true;
}

bool Empty()
{
	v.push_back("<Empty> ->");
	return true;
}
