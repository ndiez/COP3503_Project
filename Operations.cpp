#include "Operations.h"
#include "Rational.h"
#include "Irrational.h"
#include "Number.h"
#include <sstream>
#include <ostream>
#include <cmath>
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
Number * Operations::add(Number * a, Number * b) {
	Number * ans;
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
				irrAns = "( 1 + " + tt.str() + " * " + irrStr + " ) / " + tt.str();
				irrVal = b->getValue();
				ansVal = (float) (1/aDenom) + irrVal;
				ans = new Irrational(ansVal, irrAns);
			}
			else if (aDenom == 1) {
				stringstream ss, tt;
				ss<<aNum;
				tt<<aDenom;
				irrAns = ss.str() + " + " + irrStr;
				irrVal = b->getValue();
				ansVal = (float) (aNum/aDenom) + irrVal;
				ans = new Irrational(ansVal, irrAns);
			}
			else {
				stringstream ss, tt;
				ss<<aNum;
				tt<<aDenom;
				irrAns = "( " + ss.str() + " + " + tt.str() + irrStr + " )" + " / " + tt.str();
				irrVal = b->getValue();
				ansVal = (float) (aNum/aDenom) + irrVal;
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
			ansVal = (float) (1/bDenom) + irrVal;
			ans = new Irrational(ansVal, irrAns);
			}
			else if (bDenom == 1) {
			stringstream ss, tt;
			ss<<bNum;
			tt<<bDenom;
			irrAns = irrStr + " + " + ss.str();
			irrVal = a->getValue();
			ansVal = (float) (bNum/bDenom) + irrVal;
			ans = new Irrational(ansVal, irrAns);
			}
			else {
			stringstream ss, tt;
			ss<<bNum;
			tt<<bDenom;
			irrAns = "( " + tt.str() + " * " + irrStr + " + " + ss.str() + " ) / " + tt.str();
			irrVal = a->getValue();
			ansVal = (float) (bNum/bDenom) + irrVal;
			ans = new Irrational(ansVal, irrAns);
			}
		}

	}
	else {
		if((a->getType2() == "log" && b->getType2() == "log") && (a->getBase() == b->getBase())) {
			char* g = new char[a->getLogOf().size()];
			g[a->getLogOf().size()]= 0;
			memcpy(g,a->getLogOf().c_str(),a->getLogOf().size());
			char* h = new char[b->getLogOf().size()];
			h[b->getLogOf().size()]= 0;
			memcpy(h,b->getLogOf().c_str(),b->getLogOf().size());
			logofa = (float)atof(g);
			logofb = (float)atof(h);
			logofans = logofa * logofb;
			stringstream ss;
			ss<< (int) logofans;
			ansVal = a->getValue() + b->getValue();
			irrAns = "log_(" + a->getBase() + "):" + ss.str();
			ans = new Irrational(ansVal, irrAns);
		}
		else{
			irrStr  = a->toString(); // supposed to be freddys code, but its not
			irrStr2 = b->toString();
			irrAns = irrStr + " + " + irrStr2;
			irrVal = a->getValue();
			irrVal2 = b->getValue();
			ansVal = (float) irrVal + irrVal2;
			ans = new Irrational(ansVal, irrAns);
		}
	}
	ans->simplify();
	return ans;
}
Number * Operations::subtract(Number * a, Number * b) {
	Number * ans;
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
			ansVal = (float) (1/aDenom) - irrVal;
			ans = new Irrational(ansVal, irrAns);
			}
			else if (aDenom == 1) {
			stringstream ss, tt;
			ss<<aNum;
			tt<<aDenom;
			irrAns = tt.str() + " - " + irrStr;
			irrVal = b->getValue();
			ansVal = (float) (aNum/aDenom) - irrVal;
			ans = new Irrational(ansVal, irrAns);
			}
			else {
			stringstream ss, tt;
			ss<<aNum;
			tt<<aDenom;
			irrAns = "( " + ss.str() + " - " + tt.str() + irrStr + " )" + " / " + tt.str();
			irrVal = b->getValue();
			ansVal = (float) (aNum/aDenom) - irrVal;
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
			ansVal = (float) irrVal - (1/bDenom);
			ans = new Irrational(ansVal, irrAns);
			}
			else if (bDenom == 1) {
			stringstream ss, tt;
			ss<<bNum;
			tt<<bDenom;
			irrAns = irrStr + " - " + tt.str();
			irrVal = a->getValue();
			ansVal = (float) irrVal - (bNum/bDenom);
			ans = new Irrational(ansVal, irrAns);
			}
			else {
			stringstream ss, tt;
			ss<<bNum;
			tt<<bDenom;
			irrAns = "( " + tt.str() + " * " + irrStr + " - " + ss.str() + " ) / " + tt.str();
			irrVal = a->getValue();
			ansVal = (float) irrVal - (bNum/bDenom);
			ans = new Irrational(ansVal, irrAns);
			}

			}
			if((a->getType2() == "log" && b->getType2() == "log") && (a->getBase() == b->getBase())) {

				char* g = new char[a->getLogOf().size()];
				g[a->getLogOf().size()]= 0;
				memcpy(g,a->getLogOf().c_str(),a->getLogOf().size());
				char* h = new char[b->getLogOf().size()];
				h[b->getLogOf().size()]= 0;
				memcpy(h,b->getLogOf().c_str(),b->getLogOf().size());
				logofa = (float)atof(g);
				logofb = (float)atof(h);
				logofans = logofa / logofb;
				stringstream ss;
				ss<< (int) logofans;
				ansVal = a->getValue() - b->getValue();
				irrAns = "log_(" + a->getBase() + "):" + ss.str();
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
	ans->simplify();
	return ans;
}
}
Number* Operations::multiply(Number* a, Number* b) {
	Number * ans;
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
						ansVal = b->getValue() / aDenom;
						ans = new Irrational(ansVal, irrAns);
					}
					else{
						stringstream ss, tt;
						ss<<aNum;
						tt<<aDenom;
						irrAns = "( " + ss.str() + " * " + irrStr + " )" + " / " + tt.str();
						irrVal = b->getValue();
						ansVal = (float) (aNum/aDenom) * irrVal;
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
						ansVal = a->getValue() * bNum;
						ans = new Irrational(ansVal, irrAns);
					}
					else if(bNum == 1){
						stringstream ss;
						ss<<bDenom;
						irrAns = irrStr + " / " + ss.str();
						ansVal = a->getValue() / bDenom;
						ans = new Irrational(ansVal, irrAns);
					}
					else{
						stringstream ss, tt;
						ss<<bNum;
						tt<<bDenom;
						irrAns = "( " + ss.str() + " * " + irrStr + " )" + " / " + tt.str();
						irrVal = a->getValue();
						ansVal = (float) (bNum/bDenom) * irrVal;
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
	ans->simplify();
	return ans;
}
Number * Operations::divide(Number * a, Number * b) {
	Number * ans;
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
					stringstream ss, tt;
					ss<<aNum;
					tt<<aDenom;
					irrAns = ss.str() + " / ( " + tt.str() +  " * " + irrStr + " )";
					irrVal = b->getValue();
					ansVal = (float) (aNum/aDenom) / irrVal;
					ans = new Irrational(ansVal, irrAns);
				}
				else {
					bNum = b->getNum();
					bDenom = b->getDenom();
					irrStr = a->toString();
					stringstream ss, tt;
					ss<<bNum;
					tt<<bDenom;
					irrAns = "( " + irrStr + " * " + tt.str() + " ) / " + ss.str();
					irrVal = a->getValue();
					ansVal = (float) (bNum/bDenom) + irrVal;
					ans = new Irrational(ansVal, irrAns);
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
	ans->simplify();
	return ans;
}
Number * Operations::exponentiate(Number * a, Number * b) {
		Number* ans;
		if (b->getValue() == 1) {
			ans = a;
		}
		else if (a->getType() == "Rational" && b->getType() == "Rational") {
			aNum = a->getNum();
			aDenom = a->getDenom();
			bDenom = b->getDenom();
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
				aNum = a->getNum();
				aDenom = a->getDenom();
				bNum = b->getNum();
				bDenom = b->getDenom();
				Number* tempB = new Rational(bNum);
				Number* tempAns = exponentiate(a,tempB);
				stringstream ss;
				ss<<bDenom;
				string ansStr = ss.str() + "rt:" + tempAns->toString();
				ans = new Irrational(ansStr);
			}
		}
		else { //a is not rational
			string str = a->toString() + "^" + b->toString();
			float v = pow (a->getValue(), b->getValue());
			ans = new Irrational(v, str);
		}
	return ans;
}

// Converts the input string to a number so we can check if it's rational or irrational.
Number * Operations::toRational(string a) {
	Number* ans;
	for (int i =0; i < (int)a.size(); i++) {
		if (a.at(i) == '.' ) {

			int power = a.size() - (i + 1);
			a.erase(i, i);
			int tenPower = pow (10, power);
			char *b=new char[a.size()];
			b[a.size()]=0;
			memcpy(b,a.c_str(),a.size());
			ans = new Rational(atoi(b), tenPower);
			break;
		}
		else {
			char* b = new char[a.size()];
			b[a.size()]= 0;
			memcpy(b,a.c_str(),a.size());
			ans = new Rational (atoi(b));
		}
	}
	return ans;
}

Number* Operations:: toNumber(string str, Number* ansOld){
	Number* ans;
	bool noAns = true;
	bool decimalRt = false;
	string sub;

	if(str.at(0) == 'a')
	{
		str = ansOld->toString();
	}
	for(int i = 1; i < (int)str.size() && noAns && !decimalRt; i++)
	{
		if(str.at(i) == '.')
		{
			//cout << str.find(':');
			if(str.find(':') < str.length())
			{
				sub = str.substr(str.find(':'));
				str.erase(str.find(':') + 1);
				ans = toRational(sub);
				str += ans->toString();
				decimalRt = true;
			}
			else
			{
				ans = toRational(str);
				noAns = false;

			}
		}
	}

	if(noAns && (str.at(0) == 'l')  || (str.at(0) == 'e') || (str.at(0) == 'p') || (str.at(0) == 's'))
	{
		ans = new Irrational(str);
		noAns = false;
	}
	else if(noAns)
	{
		for(int i = 1; i < (int)str.size() && noAns; i++)
		{
			if(str.at(i) == 'r')
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

