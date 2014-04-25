#include "Shunting.h"
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <list>
#include <stack>
#include <vector>
using namespace std;

Shunting::Shunting() {


}
// Defining an operator map so we can set the precedence and right or left associative value for all the basic functions. 
typedef map <string, pair< int,int> > operatorMap;
const operatorMap:: value_type assocs[] =
    {  operatorMap :: value_type( "+", make_pair<int,int>( 0, 0 )),
       operatorMap:: value_type( "-", make_pair<int,int>( 0, 0 )),
       operatorMap:: value_type( "*", make_pair<int,int>( 5, 0 )),
       operatorMap:: value_type( "/", make_pair<int,int>( 5, 0 )),
       operatorMap:: value_type( "^", make_pair<int,int>( 5, 1 ))
       };

const operatorMap opmap(assocs, assocs + sizeof(assocs)/sizeof(assocs[0]));

//Testing if input token is parenthesis. 
bool Shunting::isParenthesis(const string& str)
{
    return str == "(" || str == ")";
}
//Testing if input token is operator. 
bool Shunting:: isOperator(const string& str)
{
    return str == "+" || str == "-" || str == "*" || str == "/" || str == "^";
}

//Finding out associative value for operators & returning it. 
bool Shunting::isAssociative(const string& str, int precedence)
{
	const pair<int,int> p = opmap.find(str)->second;
    if (p.second == 0) {
        return false;
    }
    else
        return true;
     // if(tkn == "+" || tkn == "-" || tkn == "/" || tkn == "*") return true;
     //else return false;
}
// Comparing precedence of operators through the operator map. 
int Shunting:: comparePrec(const string& firsttoken, const string& secondtoken ) {
 const :: pair<int,int> p1 = opmap.find(firsttoken) -> second;
 const :: pair<int,int> p2 = opmap.find(secondtoken) -> second;

    return p1.first - p2.first;
}

// Takes a string input and converts the string into a vector of tokens, so we can convert it into RPN notation. 
// Makes sure to see if each of the tokens is empty , parenthesis, operator or number. 
vector<string> Shunting::parseTokens(const string& input) {
    vector<string> tokens;
    string str = "";

    for ( int i = 0; i <= (int) input.length(); ++i)   {
        const string token(1, input [i]);

        if (isParenthesis(token) || isOperator(token))
        {
            if (!str.empty())
            {
                 tokens.push_back(str ) ;
            }
            str = "";
            tokens.push_back(token);
        }
        else {
            if (!token.empty() && token != " ")
            {
                str.append( token );
            }
            else
            {
                if (str != "")
                {
                    tokens.push_back(str);
                    str = "";
                }
			}
            if(i == (int)input.length() && str != "" && str != " ")
            	tokens.push_back(str);
		 }
    }
    	return tokens;
}

// Takes the vector of tokens and uses a stack of operators and output queue to create an RPN notation of the infix notation that is passed in. 
// Outputs a vector of tokens in the RPN notation, so it is easier to calculate. 
bool Shunting::convertInput(const vector<string>& input, const int& size, vector<string>& outputVec) {

	bool success = true;
    list <string> output;
    stack<string> opstack;
     for ( int i = 0; i < size; i++ )
    {
        const string token = input[ i ];
        if(token == " ")
        	break;
        if ( isOperator(token)) {
            const string operator1 = token;
             if (!opstack.empty())
            {
                string operator2 = opstack.top();
                while (isOperator( operator2 ) &&
                        ((isAssociative(operator1, 1) &&  comparePrec(operator1, operator2) == 0 ) ||
                        ( comparePrec( operator1, operator2 ) <= 0 )))
                {
                    opstack.pop();
                    output.push_back(operator2);

                    if (!opstack.empty())
                        operator2 = opstack.top();
                    else
                        break;
                }
            }
             opstack.push(operator1);
        }
        else if ( token == "(")
        {
            opstack.push( token );
        }
         else if ( token == ")" )
        {
            string firstToken  = opstack.top();
            while (firstToken != "(")
            {
                output.push_back(firstToken);
                opstack.pop();

                if (opstack.empty() ) break;
                firstToken = opstack.top();
            }
            if (!opstack.empty())opstack.pop();

            if ( firstToken != "(" )
            {
                return false;
            }
        }
        else
        {
            output.push_back( token );
        }
    }
    while (!opstack.empty())
    {
        const string TokenStack = opstack.top();
        if ( isParenthesis(TokenStack ))
        {
            return false;
        }
        output.push_back( TokenStack );
        opstack.pop();
    }

    outputVec.assign(output.begin(),output.end() );

    return success;
}

//Actually does the calculations
//Has to return a number because of the ans keyword
//Calls parseTokens, then convertInput, then access the number classes so the actual operations can be done. 

Number* Shunting:: evaluate(string input, Number* ansOld)
{

	Operations* o = new Operations();
	input.append(" ");
	input.append("+");
	input.append(" ");
	input.append("0");

	vector<string> tokens = parseTokens(input);
	vector<string> converted;
	stack<Number*> nums;
 	for(int i = 1; i < (int)tokens.size(); i++)
 	{
 		if(tokens[i]== "-" && (isOperator(tokens[i-1]) || isParenthesis(tokens[i-1])))
 		{
 			tokens[i + 1].insert(0, "-");
 			tokens.erase(tokens.begin() + i);
 		}
 
 	}
	if(convertInput(tokens, tokens.size(), converted))
	{
		for ( int i = 0; i < (int) converted.size(); i++ )
		{
			if ( !isOperator(converted[i]) )
			{

				try
				{
					nums.push(toNumber(converted[i], ansOld->simplify()));
				}
				catch(int e)
				{
					throw invalid_argument("Invalid expression input, please adhere to input standards.");
				}
			}
			else
			{
				Number* result;
				
				Number* n2 = nums.top();
				nums.pop();
				if (!nums.empty() )
				{
					Number* n1 = nums.top();
					nums.pop();

					if(converted[i] == "+") {
						result = o->add(n1, n2);
					}
					else if(converted[i] == "-")
						result = o->subtract(n1, n2);
					else if(converted[i] == "*")
						result = o->multiply(n1, n2);
					else if(converted[i] == "/")
						result = o->divide(n1, n2);
					else if(converted[i] == "^")
						result = o->exponentiate(n1, n2);
					else
						throw invalid_argument("Invalid expression input, please adhere to input standards.");
				}
				else
				{
					if ( converted[i] == "-" )
						result = o->multiply(n2, new Rational(-1));
					else
						result = n2;
				}

				nums.push(result->simplify());

			}
		}
	}

	else
	{
		cout << "Mismatched parenthesis. Assuming answer = 0" << endl;
		Number* result = new Rational(0);
		nums.push(result);
	}


	return nums.top()->simplify();
}
// Converts the input string to a number so we can check if it's rational or irrational. 
Number* Shunting:: toNumber(string str, Number* ansOld){
	Number* ans;
	Operations * o = new Operations();
	bool noAns = true;

	if(str.at(0) == 'a')
	{
		ans = ansOld;
		noAns = false;
	}
	if((str.at(0) == 'l')  || (str.at(0) == 'e') || (str.at(0) == 'p') || (str.at(0) == 's'))
	{
		ans = new Irrational(str);
		noAns = false;
	}
	else
	{
		for(int i = 0; i < (int)str.size() && noAns; i++)
		{
			if(str.at(i) == '.')
			{
				ans = o->toRational(str);
				noAns = false;
				break;
			}
			else if(str.at(i) == 'r')
			{
				ans = new Irrational(str);
				noAns = false;
				break;
			}
			else if(str.at(i) == '/')
			{
				char *a=new char[str.size()+1];
				a[str.substr(i-1).size()]=0;
				memcpy(a,str.c_str(),str.substr(i-1).size());

				char *b=new char[str.size()+1];
				b[str.substr(i+1).size()]=0;
				memcpy(b,str.c_str(),str.substr(i+1).size());
				ans = new Rational(atoi(a), atoi(b));
				noAns = false;
				delete[] a;
				delete[] b;
				break;
			}
		}

	}

	if(noAns)
	{
		char *c=new char[str.size()+1];
		c[str.size()]=0;
		memcpy(c,str.c_str(),str.size());
		ans = new Rational(atoi(c));
		delete[] c;
	}

	return ans;
}


Number* Shunting:: evaluate(string input)
{
	Operations* o = new Operations();

	vector<string> tokens = parseTokens(input);
	vector<string> converted;
	stack<Number*> nums;
 	for(int i = 1; i < (int)tokens.size(); i++)
 	{
 		if(tokens[i]== "-" && (isOperator(tokens[i-1]) || isParenthesis(tokens[i-1])))
 		{
 			tokens[i + 1].insert(0, "-");
 			tokens.erase(tokens.begin() + i);
 		}

 	}
	if(convertInput(tokens, tokens.size(), converted))
	{
		for ( int i = 0; i < (int) converted.size(); i++ )
		{
			if ( !isOperator(converted[i]) )
			{
				try
				{
					nums.push(toNumber(converted[i], new Rational(1)));
				}
				catch(int e)
				{
					throw invalid_argument("Invalid expression input, please adhere to input standards.");
				}
			}
			else
			{
				Number* result;

				Number* n2 = nums.top();
				nums.pop();
				if (!nums.empty() )
				{
					Number* n1 = nums.top();
					nums.pop();

					if(converted[i] == "+") {
						result = o->add(n1, n2);
					}
					else if(converted[i] == "-")
						result = o->subtract(n1, n2);
					else if(converted[i] == "*")
						result = o->multiply(n1, n2);
					else if(converted[i] == "/")
						result = o->divide(n1, n2);
					else if(converted[i] == "^")
						result = o->exponentiate(n1, n2);
					else
						throw invalid_argument("Invalid expression input, please adhere to input standards.");
				}
				else
				{
					if ( converted[i] == "-" )
						result = o->multiply(n2, new Rational(-1));
					else
						result = n2;
				}
				nums.push(result);

			}
		}
	}

	else
	{
		cout << "Mismatched parenthesis. Assuming answer = 0" << endl;
		Number* result = new Rational(0);
		nums.push(result);
	}


	return nums.top();
}
