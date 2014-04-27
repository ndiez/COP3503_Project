#include "Operations.h"
#include "Rational.h"
#include "Irrational.h"
#include "Number.h"
#include <sstream>
#include <ostream>
#include <cmath>
#include <cstring>
using namespace std;

Operations::Operations() {
	aNum = 0;
	aDenom = 0;
	bNum = 0;
	bDenom = 0;
	ansNum = 0;
	ansDenom = 0;
}
Operations::~Operations() {

}
Number* Operations::add(Number* a, Number* b) {
	Number* ans;
	if (a->getType() == "Rational" && b->getType() == "Rational") {
		aNum = a->getNum();
		aDenom = a->getDenom();
		bNum = b->getNum();
		bDenom = b->getDenom();
		ansDenom = aDenom * bDenom;
		ansNum = (aNum * bDenom) + (bNum * aDenom);
		ans = new Rational(ansNum, ansDenom);
	}
	else if ((a->getType() == "Rational" && b->getType() == "Irrational") || (b->getType() == "Rational" && a->getType() == "Irrational")) {
		if (a->getType() == "Rational") {
			aNum = a->getNum();
			aDenom = a->getDenom();
			irrStr = b->toString();
			if(aNum ==0){
				irrAns = irrStr;
				ansVal = b->getValue();
				ans = new Irrational(ansVal, irrAns);
			}
			else if (aNum == 1 && aDenom == 1) {
				irrAns = "1 + " + irrStr;
				irrVal = b->getValue();
				ansVal = 1 + irrVal;
				ans = new Irrational(ansVal, irrAns);
			}
			else if(aNum == 1) {
				stringstream tt;
				tt<<aDenom;
				irrAns = "(1 + " + tt.str() + " * " + irrStr + " ) / " + tt.str();
				irrVal = b->getValue();
				ansVal = (float) 1/aDenom + irrVal;
				ans = new Irrational(ansVal, irrAns);
			}
			else if (aDenom == 1) {
				stringstream ss, tt;
				ss<<aNum;
				tt<<aDenom;
				irrAns = ss.str() + " + " + irrStr;
				irrVal = b->getValue();
				ansVal = (float) aNum/aDenom + irrVal;
				ans = new Irrational(ansVal, irrAns);
			}
			else {
				stringstream ss, tt;
				ss<<aNum;
				tt<<aDenom;
				irrAns = "( " + ss.str() + " + " + tt.str() + irrStr + " ) / " + tt.str();
				irrVal = b->getValue();
				ansVal = (float) aNum/aDenom + irrVal;
				ans = new Irrational(ansVal, irrAns);
			}
		}
		else {
			bNum = b->getNum();
			bDenom = b->getDenom();
			irrStr = a->toString();
			if (bNum == 1 && bDenom == 1) {
				irrAns = irrStr + " + 1";
				irrVal = a->getValue();
				ansVal = 1 + irrVal;
				ans = new Irrational(ansVal, irrAns);
			}
			else if(bNum == 1) {
				stringstream tt;
				tt<<bDenom;
				irrAns = "( " + tt.str() + " * " + irrStr + " + 1 ) / " + tt.str();
				irrVal = a->getValue();
				ansVal = (float) 1/bDenom + irrVal;
				ans = new Irrational(ansVal, irrAns);
			}
			else if (bDenom == 1) {
				stringstream ss, tt;
				ss<<bNum;
				tt<<bDenom;
				irrAns = irrStr + " + " + ss.str();
				irrVal = a->getValue();
				ansVal = (float) bNum/bDenom + irrVal;
				ans = new Irrational(ansVal, irrAns);
			}
			else {
				stringstream ss, tt;
				ss<<bNum;
				tt<<bDenom;
				irrAns = "( " + tt.str() + " * " + irrStr + " + " + ss.str() + " ) / " + tt.str();
				irrVal = a->getValue();
				ansVal = (float) bNum/bDenom + irrVal;
				ans = new Irrational(ansVal, irrAns);
			}
		}
	}
	else {
		if((a->getType2() == "log" && b->getType2() == "log") && (a->getBase() == b->getBase())) {
			logofa = (float)atof(a->getLogOf().c_str());
			logofb = (float)atof(b->getLogOf().c_str());
			logofans = logofa * logofb;
			stringstream ss;
			ss<< (int) logofans;
			ansVal = a->getValue() + b->getValue();
			irrAns = "log_" + a->getBase() + ":" + ss.str();
			ans = new Irrational(ansVal, irrAns);
		}
		else{
			irrStr  = a->toString(); // supposed to be Freddy's code, but its not
			irrStr2 = b->toString();
			irrAns = irrStr + " + " + irrStr2;
			irrVal = a->getValue();
			irrVal2 = b->getValue();
			ansVal = (float) irrVal + irrVal2;
			ans = new Irrational(ansVal, irrAns);
		}
	}
	return ans;
}
Number* Operations::subtract(Number* a, Number* b) {
	Number* ans;
	if (a->getType() == "Rational" && b->getType() == "Rational") {
		aNum = a->getNum();
		aDenom = a->getDenom();
		bNum = b->getNum();
		bDenom = b->getDenom();
		ansDenom = aDenom * bDenom;
		ansNum = (aNum * bDenom) - (bNum * aDenom);
		ans = new Rational(ansNum, ansDenom);
	}
	else if ((a->getType() == "Rational" && b->getType() == "Irrational") || (b->getType() == "Rational" && a->getType() == "Irrational")) {
		if (a->getType() == "Rational") {
			aNum = a->getNum();
			aDenom = a->getDenom();
			irrStr = b->toString();
			if (aNum == 1 && aDenom == 1) {
				irrAns = "1 - " + irrStr;
				irrVal = b->getValue();
				ansVal = 1 - irrVal;
				ans = new Irrational(ansVal, irrAns);
			}
			else if(aNum == 1) {
				stringstream tt;
				tt<<aDenom;
				irrAns = "( 1 - " + tt.str() + " * " + irrStr + " ) / " + tt.str();
				irrVal = b->getValue();
				ansVal = (float) 1/aDenom - irrVal;
				ans = new Irrational(ansVal, irrAns);
			}
			else if (aDenom == 1) {
				stringstream ss;
				ss<<aNum;
				irrAns = ss.str() + " - " + irrStr;
				irrVal = b->getValue();
				ansVal = (float) aNum - irrVal;
				ans = new Irrational(ansVal, irrAns);
			}
			else {
				stringstream ss, tt;
				ss<<aNum;
				tt<<aDenom;
				irrAns = "( " + ss.str() + " - " + tt.str() + " * " + irrStr + " ) " + " / " + tt.str();
				irrVal = b->getValue();
				ansVal = (float) aNum/aDenom - irrVal;
				ans = new Irrational(ansVal, irrAns);
			}
		}
		else {
			bNum = b->getNum();
			bDenom = b->getDenom();
			irrStr = a->toString();
			if (bNum == 1 && bDenom == 1) {
				irrAns = irrStr + " - 1";
				irrVal = a->getValue();
				ansVal = irrVal - 1;
				ans = new Irrational(ansVal, irrAns);
			}
			else if(bNum == 1) {
				stringstream tt;
				tt<<bDenom;
				irrAns = "( " + tt.str() + " * " + irrStr + " - 1 ) / " + tt.str();
				irrVal = a->getValue();
				ansVal = (float) irrVal - (float) 1/bDenom;
				ans = new Irrational(ansVal, irrAns);
			}
			else if (bDenom == 1) {
				stringstream ss;
				ss<<bNum;
				irrAns = irrStr + " - " + ss.str();
				irrVal = a->getValue();
				ansVal = (float) irrVal - (float) bNum;
				ans = new Irrational(ansVal, irrAns);
			}
			else {
				stringstream ss, tt;
				ss<<bNum;
				tt<<bDenom;
				irrAns = "( " + tt.str() + " * " + irrStr + " - " + ss.str() + " ) / " + tt.str();
				irrVal = a->getValue();
				ansVal = (float) irrVal - (float) bNum/bDenom;
				
				stringstream test;
				test<<ansVal;
				cout << "ansVal = " + test.str() << endl;
				
				ans = new Irrational(ansVal, irrAns);
			}
		}
	}
	else {
			if((a->getType2() == "log" && b->getType2() == "log") && (a->getBase() == b->getBase())) {
				logofa = (float)atof(a->getLogOf().c_str());
				logofb = (float)atof(b->getLogOf().c_str());
				if (logofb != 0)
				logofans = logofa / logofb;
				else {
				cout << "Error Occurred, tried to divide by 0." << endl;
				logofans = 1;
				}
				stringstream ss;
				ss<< (int) logofans;
				ansVal = a->getValue() - b->getValue();
				irrAns = "log_" + a->getBase() + ":" + ss.str();
				ans = new Irrational(ansVal, irrAns);
			}
			else {
				irrStr  = a->toString();
				irrStr2 = b->toString();
				irrAns = irrStr + " - " + irrStr2;
				irrVal = a->getValue();
				irrVal2 = b->getValue();
				ansVal = (float) irrVal - irrVal2;
				ans = new Irrational(ansVal, irrAns);
			}
		}
	//ans->simplify();
	return ans;
}
Number* Operations::multiply(Number* a, Number* b) {
	Number* ans;
	if (a->getType() == "Rational" && b->getType() == "Rational") {
		aNum = a->getNum();
		aDenom = a->getDenom();
		bNum = b->getNum();
		bDenom = b->getDenom();
		ansDenom = aDenom * bDenom;
		ansNum = aNum * bNum;
		ans = new Rational(ansNum, ansDenom);
	}
	else if ((a->getType() == "Rational" && b->getType() == "Irrational") || (b->getType() == "Rational" && a->getType() == "Irrational")) {
		if (a->getType() == "Rational") {
					aNum = a->getNum();
					aDenom = a->getDenom();
					irrStr = b->toString();
					if(aDenom == 1 && aNum == 1){
						irrAns = irrStr;
						ansVal = b->getValue();
						ans = new Irrational(ansVal, irrAns);
					}
					else if(aDenom == 1){
						stringstream ss;
						ss<< aNum;
						irrAns = ss.str() + " * " + irrStr;
						ansVal = (float) aNum * b->getValue();
						ans = new Irrational(ansVal, irrAns);
					}
					else if(aNum == 1){
						stringstream ss;
						ss<<aDenom;
						irrAns = irrStr + " / " + ss.str();
						ansVal = b->getValue() / (float) aDenom;
						ans = new Irrational(ansVal, irrAns);
					}
					else{
						stringstream ss, tt;
						ss<<aNum;
						tt<<aDenom;
						irrAns = "( " + ss.str() + " * " + irrStr + " ) " + " / " + tt.str();
						irrVal = b->getValue();
						ansVal = (float) aNum/aDenom * irrVal;
						ans = new Irrational(ansVal, irrAns);
					}
				}
				else {
					bNum = b->getNum();
					bDenom = b->getDenom();
					irrStr = a->toString();
					if(bNum == 1 && bDenom == 1){
						irrAns = irrStr;
						ansVal = a->getValue();
						ans = new Irrational(ansVal, irrAns);
					}
					else if(bDenom == 1){
						stringstream ss;
						ss<<bNum;
						irrAns = irrStr + " * " + ss.str();
						ansVal = a->getValue() * (float) bNum;
						ans = new Irrational(ansVal, irrAns);
					}
					else if(bNum == 1){
						stringstream ss;
						ss<<bDenom;
						irrAns = irrStr + " / " + ss.str();
						ansVal = a->getValue() / (float) bDenom;
						ans = new Irrational(ansVal, irrAns);
					}
					else{
						stringstream ss, tt;
						ss<<bNum;
						tt<<bDenom;
						irrAns = "( " + ss.str() + " * " + irrStr + " )" + " / " + tt.str();
						irrVal = a->getValue();
						ansVal = (float) bNum/bDenom * irrVal;
						ans = new Irrational(ansVal, irrAns);
					}
				}

			}
			else {
				irrStr  = a->toString();
				irrStr2 = b->toString();
				irrAns = irrStr + " * " + irrStr2;
				irrVal = a->getValue();
				irrVal2 = b->getValue();
				ansVal = (float) irrVal * irrVal2;
				ans = new Irrational(ansVal, irrAns);
			}
	//ans->simplify();
	return ans;
}
Number* Operations::divide(Number* a, Number* b) {
	Number* ans;
 	if (b->getValue() == 0) {
 		cout << "Cannot divide by zero, assuming denominator = 1." << endl;
 		b = new Rational(1);
 	}
	if (a->getType() == "Rational" && b->getType() == "Rational") {
		aNum = a->getNum();
		aDenom = a->getDenom();
		bNum = b->getNum();
		bDenom = b->getDenom();
		ansDenom = aDenom * bNum;
		ansNum = aNum * bDenom;
		ans = new Rational(ansNum, ansDenom);
	}
	else if ((a->getType() == "Rational" && b->getType() == "Irrational") || (b->getType() == "Rational" && a->getType() == "Irrational")) {
		if (a->getType() == "Rational") {
				aNum = a->getNum();
				aDenom = a->getDenom();
				irrStr = b->toString();
				if(aDenom == 1 && aNum == 1){
					irrAns = "1 / " + irrStr;
					ansVal = 1 / b->getValue();
					ans = new Irrational(ansVal, irrAns);
				}
				else if(aDenom == 1){
					stringstream ss;
					ss<< aNum;
					irrAns = ss.str() + " / " + irrStr;
					ansVal = (float) aNum / b->getValue();
					ans = new Irrational(ansVal, irrAns);
				}
				else if(aNum == 1){
					stringstream ss;
					ss<<aDenom;
					irrAns = irrStr + " * " + ss.str();
					ansVal = b->getValue() * aDenom;
					ans = new Irrational(ansVal, irrAns);
				}
				else{
					stringstream ss, tt;
					ss<<aNum;
					tt<<aDenom;
					irrAns = "( " + tt.str() + " * " + irrStr + " ) / " + ss.str();
					irrVal = b->getValue();
					ansVal = (float) aDenom/aNum * irrVal;
					ans = new Irrational(ansVal, irrAns);
				}
			}
		else {
				bNum = b->getNum();
				bDenom = b->getDenom();
				irrStr = a->toString();
				if(bNum == 1 && bDenom == 1){
					irrAns = irrStr;
					ansVal = a->getValue();
					ans = new Irrational(ansVal, irrAns);
				}
				else if(bDenom == 1){
					stringstream ss;
					ss<<bNum;
					irrAns = irrStr + " / " + ss.str();
					ansVal = a->getValue() / bNum;
					ans = new Irrational(ansVal, irrAns);
				}
				else if(bNum == 1){
					stringstream ss;
					ss<<bDenom;
					irrAns = irrStr + " * " + ss.str();
					ansVal = a->getValue() * bDenom;
					ans = new Irrational(ansVal, irrAns);
				}
				else{
					stringstream ss, tt;
					ss<<bNum;
					tt<<bDenom;
					irrAns = "( " + tt.str() + " * " + irrStr + " )" + " / " + ss.str();
					irrVal = a->getValue();
					ansVal = (float) bDenom/bNum * irrVal;
					ans = new Irrational(ansVal, irrAns);
				}
			}
		}
	else {
			irrStr  = a->toString();
			irrStr2 = b->toString();
			irrAns = irrStr + " / " + irrStr2;
			irrVal = a->getValue();
			irrVal2 = b->getValue();
			ansVal = (float) irrVal / irrVal2;
			ans = new Irrational(ansVal, irrAns);
		}
	//ans->simplify();
	return ans;
}
Number* Operations::exponentiate(Number* a, Number* b) {
		Number* ans;
		if (b->getValue() == 1) {
			ans = a;
		}
		else if(b->getValue() ==0) {
			ans = new Rational(1);
		}
		else if(b->getValue() < 0) {
			if (b->getType() == "Rational")
				b = new Rational((-1 * b->getNum()), b->getDenom());
			else
				b = multiply(new Rational(-1), b);
			ans = divide(new Rational(1),exponentiate(a,b));
		}
		else if (a->getType() == "Rational" && b->getType() == "Rational") {
			aNum = a->getNum();
			aDenom = a->getDenom();
			bDenom = b->getDenom();
			int tempBDenom = bDenom;
			bNum = b->getNum();
			int tempNum = aNum;
			int tempDenom = aDenom;
			if (bDenom == 1) {
				for (int i = 1; i < bNum; i++) {
					aNum   *= tempNum;
					aDenom *= tempDenom;
				}
				ans = new Rational(aNum, aDenom);
			}
			else {
				Number* tempB = new Rational(bNum);
				Number* tempAns = exponentiate(a,tempB);
				stringstream ss;
				ss<<tempBDenom;
				string ansStr = ss.str() + "rt:" + tempAns->toString();
				ans = new Irrational(ansStr);
			}
		}
		else { //a is not rational
			string str = a->toString() + "^" + b->toString();
			float v = pow (a->getValue(), b->getValue());
			ans = new Irrational(v, str);
		}
	//ans->simplify();
	return ans;
}
Number* Operations::toRational(string a) {
	Number* ans;
	for (int i = 0; i < (int)a.size(); i++) {
		if (a.at(i) == '.' ) {
			a.erase(i, 1);
			int power = a.size() - i;
			int tenPower = pow(10, power);
			char *b=new char[a.size()];
			b[a.size()]=0;
			memcpy(b,a.c_str(),a.size());
			ans = new Rational(atoi(b), tenPower);
			delete[] b;
			break;
		}
		else {
			char* b = new char[a.size()];
			b[a.size()]= 0;
			memcpy(b,a.c_str(),a.size());
			ans = new Rational (atoi(b));
			delete[] b;
		}
	}
	return ans;
}
