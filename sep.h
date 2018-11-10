//CPSC 323
//Compiler Project
//Frank Ngo & Yifei Feng

#pragma once
#include<string>
using namespace std;

void sep(vector<string> t, string input)
{
	//point to last symbol
	int last = 0;
	//string after last symbol
	string after;
	//switch to check if the string before the symbol is invaliad
	bool swi = true;
	//conter to avoid checking a connected symbol twice
	int counter = 0;

	for (int i = 0; i < input.length(); ++i)
	{
		//the content is not alnum
		if (!isalnum(input[i]) && input[i] != '.')
		{
			if (counter == 0)
			{
				string te = input.substr(i, 2);
				//two byte token
				if (isTwo(te))
				{
					if (isOperator(te))
					{
						//the token is first of the string
						if (i == 0)
						{
							t.push_back(te);
							last += 2;
						}
						//string before the symbol may not invaliad
						else if (swi)
						{
							after = input.substr(last, i - last);
							if (isKeyword(after))
								t.push_back(after);
							else if (isIdentifier(after))
								t.push_back(after);
							else if (isInteger(after))
								t.push_back(after);
							else if (isReal(after))
								t.push_back(after);
							else
								t.push_back(after);
							t.push_back(te);
						}
						//string before the symbol is invaliad
						else
						{
							after = input.substr(last, i - last);
							t.push_back(after);
							t.push_back(te);
						}
						last = i + 2;
					}
					//same as OP
					else if (isSeparator(te))
					{
						if (i == 0)
						{
							t.push_back(te);
							last += 1;
						}
						else if (swi)
						{
							after = input.substr(last, i - last);
							if (isKeyword(after))
								t.push_back(after);
							else if (isIdentifier(after))
								t.push_back(after);
							else if (isInteger(after))
								t.push_back(after);
							else if (isReal(after))
								t.push_back(after);
							else
								t.push_back(after);
							t.push_back(te);
						}
						else
						{
							after = input.substr(last, i - last);
							t.push_back(after);
							t.push_back(te);
						}
						last = i + 2;
					}
					counter = 2;
				}
				//single byte symbol, basically same as above
				else
				{
					string te = input.substr(i, 1);
					if (isOperator(te))
					{
						if (i == 0)
						{
							t.push_back(te);
							last += 1;
						}
						else if (swi)
						{
							after = input.substr(last, i - last);
							if (isKeyword(after))
								t.push_back(after);
							else if (isIdentifier(after))
								t.push_back(after);
							else if (isInteger(after))
								t.push_back(after);
							else if (isReal(after))
								t.push_back(after);
							else
								t.push_back(after);
							t.push_back(te);
						}
						else
						{
							after = input.substr(last, i - last);
							t.push_back(after);
							t.push_back(te);
						}
						last = i + 1;
					}
					else if (isSeparator(te))
					{
						if (i == 0)
						{
							t.push_back(te);
							last += 1;
						}
						else if (swi)
						{
							after = input.substr(last, i - last);
							if (isKeyword(after))
								t.push_back(after);
							else if (isIdentifier(after))
								t.push_back(after);
							else if (isInteger(after))
								t.push_back(after);
							else if (isReal(after))
								t.push_back(after);
							else
								t.push_back(after);
							t.push_back(te);
						}
						else
						{
							after = input.substr(last, i - last);
							t.push_back(after);
							t.push_back(te);
						}
						last = i + 1;
					}
					else
						swi = false;
				}
			}
			else
				counter--;
		}
	}
	//check string after last symbol
	if (last != input.length())
	{
		after = input.substr(last, input.length() - last);
		if (isKeyword(after))
			t.push_back(after);
		else if (isIdentifier(after))
			t.push_back(after);
		else if (isInteger(after))
			t.push_back(after);
		else if (isReal(after))
			t.push_back(after);
		else
			t.push_back(after);
	}
}

//separate string
void sepa(vector<string> v, vector<string> t, vector<int> c)
{
	string input;
	for (int a = 0; a < v.size(); a++)
	{
		input = v.at(a);
		string::const_iterator fir = input.begin();
		//go to special case if not match common case
		if (isdigit(*fir))
		{
			if (isInteger(input))
				t.push_back(input);
			else if (isReal(input))
				t.push_back(input);
			else sep(t, input);
		}
		else if (isalpha(*fir))
		{
			if (isKeyword(input))
				t.push_back(input);
			else if (isIdentifier(input))
				t.push_back(input);
			else sep(t, input);
		}
		else
		{
			if (isSeparator(input))
				t.push_back(input);
			else if (isOperator(input))
				t.push_back(input);
			else sep(t, input);
		}
	}
}