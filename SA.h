#pragma once
#include<string>
// just a temp token to avoid bug notation
string token;
static int counter=1;

bool Rat18F();//1
bool Opt_Function_Definitions();//*2
bool Function_Definitions();//*3
bool Function();//4
bool Opt_Parameter_List();//*5
bool Parameter_List();//*6
bool Parameter();//7
bool Qualifier(); //8
bool Body();//9
bool Opt_Declaration_List();//*10
bool Declaration_List();//*11
bool Declaration();//12
bool IDs();//*13
bool Statement_List();//*14
bool Statement();//*15
//16 same as body
bool Assign();//17
bool If();//*18
bool Return();//*19
bool Print();//20
bool Scan();//21
bool While();//22
bool Condition();//23
bool Relop();//24
bool Expression1();//*25.1
bool Expression2();//25.2
bool Term1();//*26.1
bool Term2();//26.2
bool Factor();//27
bool Primary();//*28
bool Empty();//29

bool Rat18F() {
	Opt_Function_Definitions();
	if (token == "$$") {
		if (Opt_Declaration_List()) {
			if (Statement_List()) {
				if (token == "$$") {
					//<Rat18F> -> <Opt Function Definitions>   $$  <Opt Declaration List>  <Statement List>  $$
				}
				else {
					//error
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
		//error
		return false;
	}
	return true;
}

bool Opt_Function_Definitions() {
	if (Function_Definitions()) {
		//<Opt Function Definitions> -> <Function Definitions> 
	}
	else if (Empty()) {
		//<Opt Function Definitions> -> <Empty>
	}
	else {
		//error
		return false;
	}
	return true;
}

bool Function_Definitions() {
	if (Function()) {
		if (Function_Definitions()) {
			//<Function Definitions> -> <Function> <Function Definitions>
		}
		else {
			//<Function Definitions> -> <Function> 
		}
	}
	else {
		//error
		return false;
	}
	return true;
}

bool Function() {
	if (token == "function") {
		//lexer
		if (Identifier()) {
			if (token == "(") {
				if (Opt_Parameter_List()) {
					if (token == ")") {
						if (Opt_Declaration_List()) {
							if (Body()) {
								//<Function> -> function  <Identifier>   ( <Opt Parameter List> )  <Opt Declaration List>  <Body>
							}
							else {
								//error
								return false;
							}
						}
						else {
							//error
							return false;
						}
					}
					else {
						//error
						return false;
					}
				}
				else {
					//error
					return false;
				}
			}
			else {
				//error
				return false;
			}
		}
		else {
			//error
			return false;
		}
	}
	else {
		//error
		return false;
	}
	return true;
}

bool Opt_Parameter_List() {
	if (Parameter_List()) {
		//<Opt Parameter List> -> <Parameter List>
	}
	else if (Empty()) {
		//<Opt Parameter List> -> <Empty>
	}
	else {
		//error
		return false;
	}
	return true;
}

bool Parameter_List() {
	if (Parameter()) {
		if (token == ",") {
			if (Parameter_List()) {
				//<Parameter List> -> <Parameter> , <Parameter List>
			}
			else {
				//error
				return false;
			}
		}
		else {
			//<Parameter List> -> <Parameter>
		}
	}
	else {
		//error
		return false;
	}
	return true;
}

bool Parameter() {
	if(IDs()) {
		if (token == ":") {
			if (Qualifier()) {
				//<Parameter> -> <IDs > : <Qualifier> 
			}
			else {
				//error
				return false;
			}
		}
		else {
			//error
			return false;
		}
	}
	else {
		//error
		return false;
	}
	return true;
}

bool Qualifier() {
	if (token == "int") {
		//<Qualifier> -> int
	}
	else if(token == "boolean"){
		//<Qualifier> -> real
	}
	else if (token == "real") {
		//<Qualifier> -> real
	}
	else {
		//error
		return false;
	}
	return true;
}

bool Body() {
	if (token == "{") {
		if (Statement_List()){
			if (token == "}") {
				//<Body> -> { < Statement List> }
			}
			else {
				//error
				return false;
			}
		}
		else {
			//error
			return false;
		}
	}
	else {
		//error
		return false;
	}
	return true;
}

bool Opt_Declaration_List() {
	if (Declaration_List()) {
		//<Opt Declaration List> -> <Declaration List>
	}
	else if (Empty()) {
		//<Opt Declaration List> -> <Empty>
	}
	else {
		//error
		return false;
	}
	return true;
}

bool Declaration_List() {
	if (Declaration()) {
		if (token == ";") {
			if (Declaration_List()) {
				//<Declaration List>  -> <Declaration> ; <Declaration List>
			}
			else {
				//<Declaration List>  -> <Declaration> ;
			}
		}
		else {
			//error
			return false;
		}
	}
	else {
		//error
		return false;
	}
	return true;
}

bool Declaration() {
	if (Qualifier()) {
		if (IDs()) {
			// <Declaration> -> <Qualifier > <IDs>   
		}
		else {
			//error
			return false;
		}
	}
	else {
		//error
		return false;
	}
	return true;
}

bool IDs() {
	//lexer
	if (Identifier()) {
		if (token == ",") {
			if (IDs()) {
				//<IDs> -> <Identifier>, <IDs>
			}
			else {
				//error
				return false;
			}
		}
		else {
			//<IDs> -> <Identifier>
		}
	}
	else {
		//error
		return false;
	}
	return true;
}

bool Statement_List() {
	if (Statement()) {
		if(Statement_List()){
			//<Statement List> -> <Statement> <Statement List>
		}
		else {
			//<Statement List> -> <Statement>
		}
	}
	else {
		//error
		return false;
	}
	return true;
}

bool Statement() {
	if (Body()) {
		//<Statement> -> <Compound>
	}
	else if (Assign()) {
		//<Statement> -> <Assign>
	}
	else if (If()) {
		//<Statement> -> <If>
	}
	else if (Return()) {
		//<Statement> -> <Return>
	}
	else if (Print()) {
		//<Statement> -> <Print>
	}
	else if (Scan()) {
		//<Statement> -> <Scan>
	}
	else if (While()) {
		//<Statement> -> <While> 
	}
	else {
		//error
		return false;
	}
	return true;
}

bool Assign() {
	//lexer
	if (Identifier()) {
		if (token == "=") {
			if (Expression1()) {
				if (token == ";") {
					//<Assign> -> <Identifier> = <Expression1>;
				}
				else {
					//error
					return false;
				}
			}
			else {
				//error
				return false;
			}
		}
		else {
			//error
			return false;
		}
	}
	else {
		//error
		return false;
	}
	return true;
}

bool If() {
	//1
	if (token == "if") {
		//2
		if(token == "(") {
			//3
			if (Condition()) {
				//4
				if (token == ")") {
					//5
					if (Statement()) {
						//6
						if (token == "else") {
							//7
							if (Statement()) {
								//8
								if (token == "ifend") {
									 //<If> -> if  ( <Condition>  ) <Statement>   else  <Statement>  ifend  
								}
								//8
								else {
									//error
									return false;
								}
							}
							//7
							else {
								//error
								return false;
							}
						}
						else if (token == "ifend") {
							//<If> -> if (<Condition>) <Statement>   ifend
						}
						//6
						else {
							//error
							return false;
						}
					}
					//5
					else {
						//error
						return false;
					}
				}
				//4
				else {
					//error
					return false;
				}
			}
			//3
			else {
				//error
				return false;
			}
		}	
		//2
		else {
			//error
			return false;
		}
	}
	//1
	else {
			//error
			return false;
	}
	return true;
}

bool Return() {
	if (token == "return") {
		if (token == ";") {
			//<Return> -> return; 
			}
		else if (Expression1()) {
			if (token == ";") {
				//<Return> -> return; | return <Expression1>;
			}
			else {
				//error
				return false;
			}
		}
		else {
			//error
			return false;
		}
	}
	else {
		//error
		return false;
		}
	return true;
}

bool Print() {
	if (token == "put") {
		if (token == "(") {
			if (Expression1()) {
				if (token == ")") {
					if (token == ";") {
						//<Print> -> put ( <Expression1>);
					}
					else {
						//error
						return false;
					}
				}
				else {
					//error
					return false;
				}
			}
			else {
				//error
				return false;
			}
		}
		else {
			//error
			return false;
		}
	}
	else {
		//error
		return false;
	}
	return true;
}

bool Scan() {
	if (token == "get") {
		if (token == "(") {
			if (IDs()) {
				if (token == ")") {
					if (token == ";") {
						//<Scan> ->    get ( <IDs> );
					}
					else {
						//error
						return false;
					}
				}
				else {
					//error
					return false;
				}
			}
			else {
				//error
				return false;
			}
		}
		else {
			//error
			return false;
		}
	}
	else {
		//error
		return false;
	}
	return true;
}

bool While() {
	if (token == "while") {
		if (token == "(") {
			if (Condition()) {
				if (token == ")") {
					if(Statement()) {
					if (token == "whileend") {
						//<While> ->  while ( <Condition>  )  <Statement>  whileend
					}
					else {
						//error
						return false;
					}
				}
				else {
					//error
					return false;
				}
				}
				else {
					//error
					return false;
				}
			}
			else {
				//error
				return false;
			}
		}
			else {
				//error
				return false;
			}
		}
		else {
			//error
			return false;
		}
		return true;
}

	bool Condition() {
		if (Expression1()) {
			if (Relop()) {
				if (Expression1()) {
					//<Condition> -> <Expression1>  <Relop>   <Expression1>
				}
				else {
					//error
					return false;
				}
			}
			else {
				//error
				return false;
			}
		}
		else {
			//error
			return false;
		}
		return true;
	}

	bool Relop() {
		if (token == "==") {
			//<Relop> -> ==  
		}
		else if (token == "^=") {
			//<Relop> -> ^=
		}
		else if (token == ">") {
			//<Relop> -> >  
		}
		else if (token == "<") {
			//<Relop> -> <
		}
		else if (token == "=>") {
			//<Relop> -> =>
		}
		else if (token == "=<") {
			//<Relop> -> =<
		}
		else {
			//error
			return false;
		}
		return true;
	}

	bool Expression1() {
		if (Term2()) {
			if (Expression2()) {
				//<Expression1>  -> <Term2> <Expression2>
			}
			else {
				//error
				return false;
			}
		}
		else {
			//error
			return false;
		}
		return true;
	}

	bool Expression2() {
		if (token == "+") {
			if (Term2()) {
				if (Expression2()) {
					//<Expression2>  ->   + <Term2> <Expression2> 
				}
				else {
					//error
					return false;
				}
			}
			else {
				//error
				return false;
			}
		}
		else if (token == "-") {
			if (Term2()) {
				if (Expression2()) {
					//<Expression2>  ->   - <Term2> <Expression2>
				}
				else {
					//error
					return false;
				}
			}
			else {
				//error
				return false;
			}
		}
		else if (Empty()) {
			
		}
		else {
			//error
			return false;
		}
		return true;
	}

	bool Term1() {
		if (Factor()) {
			if (Term2()) {
				//<Term2>  -> <Factor> <Term2>
			}
			else {
				//error
				return false;
			}
		}
		else {
			//error
			return false;
		}
		return true;
	}
	//???
	bool Term2() {
		if (token == "*") {
			if (Factor()) {
				if (Term2()) {
					//<Term2>    -> *  <Factor> <Term2> 
				}
				else {
					//error
					return false;
				}
			}
			else {
				//error
				return false;
				}
		}
		else if (token == "/") {
			if (Factor()) {
				if (Term2()) {
					//<Term> -> /  <Factor> <Term>
				}
				else {
					//error
					return false;
				}
			}
		else {
				//error
				return false;
		}
		}
		else if (Factor()) {
			//<Term> -> <Factor>
		}
		else {
			//error
			return false;
		}
		return true;
	}

	bool Factor() {
		if (token == "-") {
			if (Primary()) {
				//<Factor> -> -<Primary>
			}
			else {
				//error
				return false;
			}
		}
		else if (Primary()) {
			//<Factor> -> <Primary>
		}
		else {
			//error
			return false;
		}
		return true;
	}

	bool Primary() {
		//lexer
		if (Identifier()) {
			if (token == "(") {
				if (IDs()) { 
					if (token == ")") {
						//<Primary> -> <Identifier>  (<IDs>)
					}
					else {
						//error
						return false;
					}
				}
				else {
					//error
					return false;
				}
			}
			else {
				//<Primary> -> <Identifier>
			}
		}
		//lexer
		else if (Integer()) {
			//<Primary> -> <Integer>
		}
		else if (token=="(") {
			if (Expression1()) {
				if (token == ")") {
					//<Primary> -> ( <Expression> )
				}
				else {
					//error
					return false;
				}
			}
			else {
				//error
				return false;
			}
		}
		//lexer
		else if (Real()) {
			//<Primary> -> <Real>
		}
		else if (token == "true") {
			//<Primary> -> true
		}
		else if (token=="false") {
			//<Primary> -> false
		}
		else {
			//error
			return false;
		}
		return true;
	}

	bool Empty() {
		//<Empty>   -> 
		return true;
	}