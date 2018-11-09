#pragma once
#include<string>
using namespace std;

//pro1: where to put counter

string token;
static int counter;
vector<string> t;
vector<string> v;
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

void passvec1(vector<string> to) {
	t = to;
}

void passvec2(vector<string> ou) {
	ou = v;
}

string gettoken() {
	if (i < t.size()) {
		string temp = t[i];
		i++;
		return temp;
	}
	else {
		return " ";
	}
}

bool Rat18F() {
	if (Opt_Function_Definitions()) {
		token = gettoken();
		if (token == "$$") {
			lexer(v, token);
			if (Opt_Declaration_List()) {
				if (Statement_List()) {
					token = gettoken();
					if (token == "$$") {
						lexer(v, token);
						v.push_back("<Rat18F> -> <Opt Function Definitions>   $$  <Opt Declaration List>  <Statement List>  $$");
					}
					else {
						lexer(v, token);
						v.push_back("'$$' expected");
						return false;
					}
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			lexer(v, token);
			v.push_back("'$$' expected");
			return false;
		}
	}
	else {
		return false;
	}
	return true;
}

bool Opt_Function_Definitions() {
	if (Function_Definitions()) {
		v.push_back("<Opt Function Definitions> -> <Function Definitions>");
	}
	else if (Empty()) {
		v.push_back("<Opt Function Definitions> -> <Empty>"); 
	}
	else {
		return false;
	}
	return true;
}

bool Function_Definitions() {
	if (Function()) {
		if (Function_Definitions()) {
			v.push_back("<Function Definitions> -> <Function> <Function Definitions>"); 
		}
		else if(Empty()){
			v.push_back("<Function Definitions> -> <Function> ");
		}
	}
	else {
		return false;
	}
	return true;
}

bool Function() {
	token = gettoken();
	if (token == "function") {
		lexer(v, token);
		token = gettoken();
		if (isIdentifier(token)) {
			lexer(v, token);
			token = gettoken();
			if (token == "(") {
				lexer(v, token);
				if (Opt_Parameter_List()) {
					token = gettoken();
					if (token == ")") {
						lexer(v, token);
						if (Opt_Declaration_List()) {
							if (Body()) {
								v.push_back("<Function> -> function  <Identifier>   ( <Opt Parameter List> )  <Opt Declaration List>  <Body>"); 
							}
							else {
								return false;
							}
						}
						else {
							return false;
						}
					}
					else {
						lexer(v, token);
						v.push_back("')' expected"); 
						return false;
					}
				}
				else {
					return false;
				}
			}
			else {
				lexer(v, token);
				v.push_back("'(' expected"); 
				return false;
			}
		}
		else {
			lexer(v, token);
			v.push_back("Identifier expected"); 
			return false;
		}
	}
	else {
		lexer(v, token);
		v.push_back("'function' expected"); 
		return false;
	}
	return true;
}

bool Opt_Parameter_List() {
	if (Parameter_List()) {
		v.push_back("<Opt Parameter List> -> <Parameter List>"); 
	}
	else if (Empty()) {
		v.push_back("<Opt Parameter List> -> <Empty>"); 
	}
	else {
		return false;
	}
	return true;
}

bool Parameter_List() {
	if (Parameter()) {
		token = gettoken();
		if (token == ",") {
			lexer(v, token);
			if (Parameter_List()) {
				v.push_back("<Parameter List> -> <Parameter> , <Parameter List>"); 
			}
			else {
				return false;
			}
		}
		else {
			v.push_back("<Parameter List> -> <Parameter>"); 
		}
	}
	else {
		return false;
	}
	return true;
}

bool Parameter() {
	if(IDs()) {
		token = gettoken();
		if (token == ":") {
			lexer(v, token);
			if (Qualifier()) {
				v.push_back("<Parameter> -> <IDs > : <Qualifier>"); 
			}
			else {
				return false;
			}
		}
		else {
			lexer(v, token);
			 v.push_back("':' expected"); 
			return false;
		}
	}
	else {
		return false;
	}
	return true;
}

bool Qualifier() {
	token = gettoken();
	if (token == "int") {
		lexer(v, token);
		v.push_back("<Qualifier> -> int"); 
	}
	else if(token == "boolean"){
		lexer(v, token);
		v.push_back("<Qualifier> -> real"); 
	}
	else if (token == "real") {
		lexer(v, token);
		v.push_back("<Qualifier> -> real"); 
	}
	else {
		lexer(v, token);
		v.push_back("'int', 'boolean', 'real' expected"); 
		return false;
	}
	return true;
}

bool Body() {
	token = gettoken();
	if (token == "{") {
		lexer(v, token);
		if (Statement_List()){
			token = gettoken();
			if (token == "}") {
				lexer(v, token);
				v.push_back("<Body> -> { < Statement List> }"); 
			}
			else {
				lexer(v, token);
				v.push_back("'}' expected"); 
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		lexer(v, token);
		v.push_back("'{' expected"); 
		return false;
	}
	return true;
}

bool Opt_Declaration_List() {
	if (Declaration_List()) {
		v.push_back("<Opt Declaration List> -> <Declaration List>"); 
	}
	else if (Empty()) {
		v.push_back("<Opt Declaration List> -> <Empty>"); 
	}
	else {
		return false;
	}
	return true;
}

bool Declaration_List() {
	if (Declaration()) {
		token = gettoken();
		if (token == ";") {
			lexer(v, token);
			if (Declaration_List()) {
				v.push_back("<Declaration List>  -> <Declaration> ; <Declaration List>"); 
			}
			else {
				v.push_back("<Declaration List>  -> <Declaration> ;"); 
			}
		}
		else {
			lexer(v, token);
			v.push_back("';' expected");
			return false;
		}
	}
	else {
		return false;
	}
	return true;
}

bool Declaration() {
	if (Qualifier()) {
		if (IDs()) {
			v.push_back("<Declaration> -> <Qualifier > <IDs>"); 
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
	return true;
}

bool IDs() {
	//lexer
	if (isIdentifier(token)) {
		token = gettoken();
		if (token == ",") {
			lexer(v, token);
			if (IDs()) {
				v.push_back("<IDs> -> <Identifier>, <IDs>"); 
			}
			else {
				return false;
			}
		}
		else {
			v.push_back("<IDs> -> <Identifier>");
		}
	}
	else {
		lexer(v, token);
		v.push_back("identifier expected"); 
		return false;
	}
	return true;
}

bool Statement_List() {
	if (Statement()) {
		if(Statement_List()){
			v.push_back("<Statement List> -> <Statement> <Statement List>"); 
		}
		else {
			v.push_back("<Statement List> -> <Statement>"); 
		}
	}
	else {
		return false;
	}
	return true;
}

bool Statement() {
	bool swi=false;
	if (Compound()) {
		swi = true;
		Compound();
		v.push_back("<Statement> -> <Compound>"); 
	}
	else if (Assign()) {
		swi = true;
		Compound();
		v.push_back("<Statement> -> <Assign>"); 
	}
	else if (If()) {
		swi = true;
		Compound();
		v.push_back("<Statement> -> <If>"); 
	}
	else if (Return()) {
		swi = true;
		Compound();
		v.push_back("<Statement> -> <Return>"); 
	}
	else if (Print()) {
		swi = true;
		Compound();
		v.push_back("<Statement> -> <Print>"); 
	}
	else if (Scan()) {
		swi = true;
		Compound();
		v.push_back("<Statement> -> <Scan>"); 
	}
	else if (While()) {
		swi = true;
		Compound();
		v.push_back("<Statement> -> <While>"); 
	}
	else {
		lexer(v, token);
		v.push_back("'{ <Statement List> }', '<Identifier> = <Expression> ;' ,'if ( <Condition> ) <Statement> ifend | if (<Condition>) <Statement> else <Statement> ifend ', 'return; | return <Expression>;', 'put ( <Expression>);', 'get ( <IDs> );', 'while ( <Condition> ) <Statement> whileend' expected"); 
		return false;
	}
	return true;
}

bool Compound() {
	token = gettoken();
	if (token == "{") {
		lexer(v, token);
		if (Statement_List()) {
			token = gettoken();
			if (token == "}") {
				lexer(v, token);
				v.push_back("<Compound> -> { < Statement List> }"); 
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
	return true;
}

bool Assign() {
	if (isIdentifier(token)) {
		lexer(v, token);
		token = gettoken();
		if (token == "=") {
			lexer(v, token);
			if (Expression1()) {
				token = gettoken();
				if (token == ";") {
					lexer(v, token);
					v.push_back("<Assign> -> <Identifier> = <Expression1>;"); 
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
	return true;
}

bool If() {
	//1
	if (token == "if") {
		lexer(v, token);
		//2
		token = gettoken();
		if(token == "(") {
			lexer(v, token);
			//3
			token = gettoken();
			if (Condition()) {
				//4
				token = gettoken();
				if (token == ")") {
					lexer(v, token);
					//5
					if (Statement()) {
						//6
						token = gettoken();
						if (token == "else") {
							lexer(v, token);
							//7
							if (Statement()) {
								//8
								token = gettoken();
								if (token == "ifend") {
									lexer(v, token);
									v.push_back("<If> -> if  ( <Condition>  ) <Statement>   else  <Statement>  ifend"); 
								}
								//8
								else {
									return false;
								}
							}
							//7
							else {
								return false;
							}
						}
						else if (token == "ifend") {
							lexer(v, token);
							v.push_back("<If> -> if (<Condition>) <Statement> ifend"); 
						}
						//6
						else {
							return false;
						}
					}
					//5
					else {
						return false;
					}
				}
				//4
				else {
					return false;
				}
			}
			//3
			else {
				return false;
			}
		}	
		//2
		else {
			return false;
		}
	}
	//1
	else {
			return false;
	}
	return true;
}

bool Return() {
	if (token == "return") {
		lexer(v, token);
		token = gettoken();
		if (token == ";") {
			lexer(v, token);
			v.push_back("<Return> -> return;"); 
			}
		else if (Expression1()) {
			token = gettoken();
			if (token == ";") {
				lexer(v, token);
				v.push_back("<Return> -> return; | return <Expression1>;"); 
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
		}
	return true;
}

bool Print() {
	if (token == "put") {
		lexer(v, token);
		token = gettoken();
		if (token == "(") {
			lexer(v, token);
			token = gettoken();
			if (Expression1()) {
				token = gettoken();
				if (token == ")") {
					lexer(v, token);
					token = gettoken();
					if (token == ";") {
						lexer(v, token);
						v.push_back("<Print> -> put ( <Expression1>);"); 
					}
					else {
						return false;
					}
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
	return true;
}

bool Scan() {
	if (token == "get") {
		lexer(v, token);
		token = gettoken();
		if (token == "(") {
			lexer(v, token);
			if (IDs()) {
				token = gettoken();
				if (token == ")") {
					lexer(v, token);
					token = gettoken();
					if (token == ";") {
						lexer(v, token);
						v.push_back("<Scan> -> get ( <IDs> );");
					}
					else {
						return false;
					}
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
	return true;
}

bool While() {
	if (token == "while") {
		lexer(v, token);
		token = gettoken();
		if (token == "(") {
			lexer(v, token);
			if (Condition()) {
				token = gettoken();
				if (token == ")") {
					lexer(v, token);
					if(Statement()) {
						token = gettoken();
					if (token == "whileend") {
						lexer(v, token);
						v.push_back("<While> ->  while ( <Condition>  )  <Statement>  whileend"); 
					}
					else {
						return false;
					}
				}
				else {
					return false;
				}
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
			else {
				return false;
			}
		}
		else {
			return false;
		}
		return true;
}

	bool Condition() {
		if (Expression1()) {
			if (Relop()) {
				if (Expression1()) {
					v.push_back("<Condition> -> <Expression1>  <Relop>   <Expression1>"); 
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
		return true;
	}

	bool Relop() {
		token = gettoken();
		if (token == "==") {
			lexer(v, token);
			v.push_back("<Relop> -> =="); 
		}
		else if (token == "^=") {
			lexer(v, token);
			v.push_back("<Relop> -> ^="); 
		}
		else if (token == ">") {
			lexer(v, token);
			v.push_back("<Relop> -> >");  
		}
		else if (token == "<") {
			lexer(v, token);
			v.push_back("<Relop> -> <"); 
		}
		else if (token == "=>") {
			lexer(v, token);
			v.push_back("<Relop> -> =>"); 
		}
		else if (token == "=<") {
			lexer(v, token);
			v.push_back("<Relop> -> =<"); 
		}
		else {
			lexer(v, token);
			v.push_back("'==', '^=', '>', '<', '=>', '=<' expected"); 
			return false;
		}
		return true;
	}

	bool Expression1() {
		if (Term2()) {
			if (Expression2()) {
				v.push_back("<Expression1>  -> <Term2> <Expression2>"); 
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
		return true;
	}

	bool Expression2() {
		token = gettoken();
		if (token == "+") {
			lexer(v, token);
			if (Term2()) {
				if (Expression2()) {
					v.push_back("<Expression2>  ->   + <Term2> <Expression2>"); 
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else if (token == "-") {
			lexer(v, token);
			if (Term2()) {
				if (Expression2()) {
					v.push_back("<Expression2> -> - <Term2> <Expression2>"); 
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else if (Empty()) {
			v.push_back("<Expression2> -> <Empty>"); 
		}
		else {
			return false;
		}
		return true;
	}

	bool Term1() {
		if (Factor()) {
			if (Term2()) {
				v.push_back("<Term2> -> <Factor> <Term2>"); 
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
		return true;
	}

	bool Term2() {
		token = gettoken();
		if (token == "*") {
			lexer(v, token);
			if (Factor()) {
				if (Term2()) {
					v.push_back("<Term2> -> * <Factor> <Term2>"); 
				}
				else {
					return false;
				}
			}
			else {
				return false;
				}
		}
		else if (token == "/") {
			lexer(v, token);
			if (Factor()) {
				if (Term2()) {
					v.push_back("<Term> -> /  <Factor> <Term>"); 
				}
				else {
					return false;
				}
			}
		else {
				return false;
		}
		}
		else if (Empty()) {
			v.push_back("<Term2> -> <Empty>"); 
		}
		else {
			return false;
		}
		return true;
	}

	bool Factor() {
		token = gettoken();
		if (token == "-") {
			lexer(v, token);
			if (Primary()) {
				v.push_back("<Factor> -> -<Primary>"); 
			}
			else {
				return false;
			}
		}
		else if (Primary()) {
			v.push_back("<Factor> -> <Primary>"); 
		}
		else {
			return false;
		}
		return true;
	}

	bool Primary() {
		token = gettoken();
		if (isIdentifier(token)) {
			lexer(v, token);
			token = gettoken();
			if (token == "(") {
				lexer(v, token);
				if (IDs()) { 
					token = gettoken();
					if (token == ")") {
						lexer(v, token);
						v.push_back("<Primary> -> <Identifier>  (<IDs>)"); 
					}
					else {
						lexer(v, token);
						v.push_back("')' expected"); 
						return false;
					}
				}
				else {
					return false;
				}
			}
			else {
				v.push_back("<Primary> -> <Identifier>"); 
			}
		}
		else if (isInteger(token)) {
			lexer(v, token);
			v.push_back("<Primary> -> <Integer>"); 
		}
		else if (token=="(") {
			lexer(v, token);
			if (Expression1()) {
				token = gettoken();
				if (token == ")") {
					lexer(v, token);
					v.push_back("<Primary> -> ( <Expression> )"); 
				}
				else {
					lexer(v, token);
					v.push_back("')' expected"); 
					return false;
				}
			}
			else {
				return false;
			}
		}
		else if (isReal(token)) {
			lexer(v, token);
			v.push_back("<Primary> -> <Real>");
		}
		else if (token == "true") {
			lexer(v, token);
			v.push_back("<Primary> -> true"); 
		}
		else if (token=="false") {
			lexer(v, token);
			v.push_back("<Primary> -> false"); 
		}
		else {
			lexer(v, token);
			v.push_back("'Identifier', 'Integer', 'Identifier ( <IDs> )', '( <Expression> )', 'Real', 'true', 'false' expected"); 
			return false;
		}
		return true;
	}

	bool Empty() {
		v.push_back("<Empty> ->"); 
		return true;
	}