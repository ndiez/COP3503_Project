#include "Rational.h"
#include <string>
#include <sstream>
using namespace std;

Rational::Rational(int numerator){
	this->numerator = numerator;
	this->denominator = 1;
	sType = "Rational";
	fValue = numerator;
}
Rational::Rational(int numerator, int denominator){
	if(denominator == 0){
		cout<< "Cannot divide by zero, assuming denominator = 1." << endl;
		denominator = 1;
	}
 	if(denominator < 0)
 	{
 		numerator *= -1;
 		denominator *= -1;
 	}
	this->numerator = numerator;
	this->denominator = denominator;

	sType = "Rational";
	fValue = (float)numerator / (float)denominator;

}


int Rational::getNum(){
	return this->numerator;
}

int Rational::getDenom(){
	return this->denominator;
}


//if denominator = 1, return the numerator as a string
//else return "numerator '/' denominator"
string Rational::toString() {
	string number;
	if (fValue == (int)fValue) {
		stringstream ss;
		ss<<(int)fValue;
		number= ss.str();
	}

	else if (this->denominator == 0) {
		return "Cannot divide by zero.";
	}
	else if (this->numerator == 0) {
		return "0";
	}
	else if (this->numerator == this->denominator) {
		return "1";
	}
	else if (this->denominator == 1) {
		stringstream ss;
		ss<<this->numerator;
		number = ss.str();
	}
	else {
		stringstream ss, tt;
		ss<<this->numerator;
		tt<<this->denominator;
		number = ss.str() + "/" + tt.str();
	}
	return number;
}
string Rational::getType()
{
	return this->sType;
}

float Rational::getValue()
{
	return this->fValue;
}
Number* Rational::simplify() {
	int a= this->getNum();
	int b = this->getDenom();
	if (a == b) {
		Number* one = new Rational(1, 1);
		return one;
	}
	else if (b == 1) {
		Number* integer = new Rational(a, 1);
		return integer;
	}
	for (int j = 0; j < 10; j++ ){
		if (a < b) {
			for (int i = 2; i < b; i++) {
				if (a % i == 0 && b % i == 0) {
					a /= i;
					b /= i;
				}
			}
		}
		else if (a > b) {
			for (int i = 2; i < a; i++) {
				if (b % i == 0 && a % i == 0) {
					a /= i;
					b /= i;
				}
			}
		}
		else {
			a = 1;
			b = 1;
		}
	}
	Number* fraction = new Rational(a, b);
	return fraction;
}
string Rational::getType2() {
	return "";
}
string Rational::getBase() {
	return "";
}
string Rational::getLogOf() {
	return "";
}
