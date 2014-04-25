#ifndef SHUNTING_H_
#define SHUNTING_H_
#include "Number.h"
#include "Rational.h"
#include "Irrational.h"
#include "Operations.h"
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <list>
#include <stack>
#include <vector>
#include <stdlib.h>

using namespace std;

class Shunting {
public:
    Shunting();
	//Actually does the calculations
	//Has to return a number because of the ans keyword
	//Calls parseTokens, then convertInput, then preforms the calculations using rationals, irrationals.
	Number* evaluate(string input, Number* ansOld);
	Number* evaluate(string input);
	Number* toNumber(string str, Number* ansOld);
private:

    typedef map <string, pair<int,int > > operatorMap;

	vector <string> parseTokens(const string & str);

	//Rearranges the elements into PEMDAS. 
	// Input required is a vector of tokens that contain the expression in infix notation. 
	// Outputs the vector of tokens in RPN notation. 
	bool convertInput(const vector<string>& input, const int& size, vector<string>& output);

	//Called by parseTokens then convertInput
	bool isParenthesis(const string& str);

	//Called by all three methods- finds if token is operator. 
	bool isOperator(const string& str);

	//Called only by convertInput, finds if token is left or right associative. 
	bool isAssociative(const string& str, int precedence);

	//Compares Operation order precedence
	int comparePrec(const string& firsttoken, const string& secondtoken );

	//Converts decimals to fractions. 
	Rational toFraction(float f);
};
#endif
