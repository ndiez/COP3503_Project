#ifndef RATIONAL_H_
#define RATIONAL_H_
#include "Number.h"
#include <string>
using namespace std;
class Rational : public Number {
public:
    // This rational class takes cares of all rational numbers, using specific methods depending on the type of operation required. 
	Rational(int numerator,int denominator);
	// integer constructor
	Rational(int numerator);
	// Getting the numerator & denominator of all the integer values. 
	int getNum();
	int getDenom();
    // Following methods simplify the expression, get the toString, type & float value of numbers and the base/(log of)  if it is a log.
	Number* simplify();
	string toString();
	string getType();
	float getValue();
	string getType2();
	string getBase();
	string getLogOf();

private:
	int numerator, denominator;
	//Shows that the number is a rational number. 
	string stype;
};

#endif /* RATIONAL_H_ */
