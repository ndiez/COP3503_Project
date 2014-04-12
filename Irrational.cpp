
#include "Irrational.h"
#include <cmath>
#include <stdlib.h>

Irrational::Irrational(){
}

Irrational::Irrational(string irr){
	if(irr.at(0) == 'e'){
		sType = "e";
		fValue = 2.71828;
	}
	else if(irr.at(0) == 'l'){
		sType = "log";
		int i;
		for(i = 4; ':'!=irr.at(i); i++){
			base += irr.at(i);
		}
		for(i += 1; i<irr.length(); i++){
			logOf = irr.at(i);
		}
		//fValue = ((log (a) / (log (atol(base));
	}
	else if(irr.at(0) == 'p' || irr.at(0) == 'P'){
		sType = "pi";
		fValue = 3.14159;
	}
	else if(irr.at(0) == 's'){
		sType = "nrt";
		n = 2;
		for(int i = 5; i < irr.length(); i++){
			rootOf += irr.at(i);
		}
		//fValue = sqrt (strToD sqrtOf);
	}
	else if(irr.at(0) == ('0' || '1' || '2' || '3' || '4' || '5' || '6' || '7' || '8' || '9')){
		sType = "nrt";
		int i = 0;
		for(i = 0; 'r' != irr.at(i); i++){
			n = irr.at(i);
		}
		for(i += 3; i < irr.length(); i++){
			rootOf += irr.at(i);
		}
		//fValue = pow (strToD rootOf, (1/n));
	}
	else{
		cout<< "Error...not an irrational number" << endl;
	}
}

string Irrational::getType(){
	return sType;
}

string Irrational::toString(){
	string str;
	if(sType == "e"){
		str = "e";
		return str;
	}
	else if(sType == "pi"){
		str = "pi";
		return str;
	}
	else if(sType == "log"){
		str = "log_" + base + ":" + logOf;
		return str;
	}
	else if(sType == "nrt"){
		if(n == "2"){
			str = "sqrt:" + rootOf;
		}
		else{
			str = n + "rt:" + rootOf;
		}
		return str;
	}
	else{
		return "No toString...error";
	}
}

float Irrational::getValue(){
	return fValue;
}

Number* Irrational::simplify(){

}
