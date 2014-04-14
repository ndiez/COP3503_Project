#ifndef OPERATIONS_H_
#define OPERATIONS_H_
#include "Number.h"
#include <stdlib.h>
#include <iostream>
#include <string>
class Operations {
    // This class does all the operations for number types. 
public:
    // Public operations include add, subtract, multiply, divide, and exponentiate. 
	Operations();
	~Operations();
	Number* add(Number* a, Number* b);
	Number* subtract(Number* a, Number* b);
	Number* multiply(Number* a, Number* b);
	Number* divide(Number* a, Number* b);
	Number* exponentiate(Number* a, Number* b);
	Number* toRational(string a);
private:
    // Private requirements for setting numerator & denominators, irrational values, logs, etc. 
	int aNum, aDenom, bNum, bDenom, ansNum, ansDenom;
	float irrVal, irrVal2, ansVal, logofa, logofb, logofans;
	string irrAns, irrStr, irrStr2;
};
#endif /*OPERATIONS_H_*/
