#include "Irrational.h"
#include "Operations.h"
#include "Shunting.h"
#include <cmath>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include <list>

Irrational::Irrational(){
}

Irrational::Irrational(float z, string irr){ //used for creating irrationals that contain operations
	sType = "Irrational";
	fValue = z;
	type = irr;
}

Irrational::Irrational(string irr){ //the constructor that is given a number and figures out which type
	sType = "Irrational";           //of irrational it is and creates it
	if(irr.at(0) == 'e'){
		type = "e";
		fValue = 2.71828;
	}
	else if(irr.at(0) == 'l'){
		type = "log";
		int i;
		bool isPow = false;
		for(i = 4; irr.at(i) != ':'; i++){
			if (irr.at(i) == ':') {
				break;
			}
			else {
				base += irr.at(i);
			}
		}
		for(i; i < (int)irr.length(); i++){
			if (irr.at(i) == ':') {
			}
			else {
				logOf += irr.at(i);
				if(irr.at(i) == '^'){
					isPow = true;
				}
			}
		}
		if(isPow == true){
			string ans;
			for(int i = base.length()+1; i < logOf.length(); i++){
				ans += logOf.at(i);
				cout << ans + "made it" << endl;
			}
			fValue = atof(ans.c_str());
		}
		if(logOf == base){
			fValue = 1;
		}
		else if(base == "e"){
			double a = atof(logOf.c_str());
			fValue = log (a) / log (2.71828);
		}
		else if(logOf == "e"){
			double a = atof(base.c_str());
			fValue = log (2.71828) / log (a);
		}
		else if(base == "pi"){
			double a = atof(logOf.c_str());
			fValue = log (a) / log (3.14159);
		}
		else if(logOf == "pi"){
			double a = atof(base.c_str());
			fValue = log (3.14159) / log (a);
		}
		else{
			double a = atof(logOf.c_str());
			double b = atof(base.c_str());
			fValue = ( log (a)/ log (b));
		}
	}
	else if(irr.at(0) == 'p' || irr.at(0) == 'P'){
		type = "pi";
		fValue = 3.14159;
	}
	else if(irr.at(0) == 's'){
		type = "nrt";
		n = 2;
		for(int i = 5; i < (int)irr.length(); i++){
			rootOf += irr.at(i);
		}
		double b = atof(rootOf.c_str());
		fValue = sqrt (b);
	}
	else if( irr.at(0) == '0' || irr.at(0) == '1' || irr.at(0) == '2' || irr.at(0) == '3' || irr.at(0) == '4' || irr.at(0) == '5' || irr.at(0) == '6' || irr.at(0) == '7' || irr.at(0) == '8' || irr.at(0) == '9'){
		type = "nrt";
		int i = 0;
		for(i = 0; 'r' != irr.at(i); i++){
			n = irr.at(i);
		}
		for(i += 3; i < (int)irr.length(); i++){
			rootOf += irr.at(i);
		}
 	//	if(rootOf.find("/0")){
 	//		cout << "Cannot divide by 0. Assuming denominator = 1." << endl;
 	//		type = "NaN";        //Should fix the 3rt:27/0 problem
 	//		fValue = 0;
 	//	}
 		//else{
 			double a = atof(n.c_str());
 			double b = atof(rootOf.c_str());
 			fValue = pow (b, (1/a));
 		//}
	}
	else{
		cout<< "Error...not an irrational number" << endl;
	}
}

string Irrational::getType(){
	return sType;             //is used to tell other classes that the number is irrational
}
string Irrational::getType2(){
	return type;              //gives the specific type of irrational
}
string Irrational::getBase(){
	return base;              //returns base of a log irrational
}
string Irrational::getLogOf(){
	return logOf;             //returns what the log is being taken of
}

string Irrational::toString(){  //prints the string of the irrational
	string str;
	if (this->fValue == (int)this->fValue) {
		stringstream ss;
		ss<<(int)fValue;
		str= ss.str();
	}
	else if(type == "e"){
		str = "e";
	}
	else if(type == "pi"){
		str = "pi";
	}
	else if(type == "log"){
		double a = atof(logOf.c_str());
		double b = atof(base.c_str());
		if(b > a){
			double value = ( log (b)/ log (a));
			if(value == (int) value){
				stringstream ss;
				ss<<(int)value;
				str = "1/" + ss.str();
			}
			else if(fValue != 1)
				str = "log_" + base + ":" + logOf;
			else
				str = "1";
		}
		else if(fValue != 1)
			str = "log_" + base + ":" + logOf;
		else
			str = "1";
	}
	else if(type == "nrt"){
		if(fValue == (int) fValue){
		stringstream ss;
		ss<<(int)fValue;
			str = ss.str();
		}
		else if(n == "2"){
			str = "sqrt:" + rootOf;
		}
		else{
			str = n + "rt:" + rootOf;
		}
	}
	else if (!type.empty()) {
		return this->type;
	}
	else{
		return "Error: no string for this Irrational.";
	}
	return str;
}

float Irrational::getValue(){
	return fValue;         //gets the float value of the irrational
}

Number* Irrational::simplify(){
	Operations* o = new Operations();
	if(1000 * fValue == (int)fValue * 1000) {
		stringstream ss;
		ss << (float)fValue;
		return o->toRational(ss.str());
	}
	else  {
		return this;
	}
	//Shunting* s = new Shunting();
	//Number* simplified = s->evaluate(this->toString());
	//	return simplified;
}
int Irrational::getNum() {
	return 0;
}
int Irrational::getDenom() {
	return 0;
}
