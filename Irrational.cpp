

#include "Irrational.h"
#include <cmath>

Irrational::Irrational(){
}

Irrational::Irrational(string irr){
	if(irr.charAt(0) == 'e'){
		sType = "e";
		fValue = 2.7;
	}
	else if(irr.chatAt(0) == 'l'){
		sType = "log";
		int i;
		for(i = 4; ':'!=irr.charAt(i); i++){
			base += irr.charAt(i);
		}
		for(i += 1; i<irr.length(); i++){
			logOf = irr.charAt(i);
		}
		//fValue = (log (strToD logOf)/log (base);
	}
	else if(irr.chatAt(0) == 'p' || irr.charAt(0) == 'P'){
		sType = "pi";
		fValue = 3.14159;
	}
	else if(irr.charAt(0) == 's'){
		sType = "sqrt";
		for(int i = 5; i < irr.length(); i++){
			sqrtOf += irr.charAt(i);
		}
		//fValue = sqrt (strToD sqrtOf);
	}
	else if(irr.charAt(0) == ('0' || '1' || '2' || '3' || '4' || '5' || '6' || '7' || '8' || '9')){
		sType = "nrt";
		int i = 0;
		for(i = 0; 'r' != irr.charAt(i); i++){
			n = irr.charAt(i);
		}
		for(i += 3; i < irr.length(); i++){
			rootOf += irr.charAt(i);
		}
		//fValue = pow (strToD rootOf, (1/n));
	}
	else{
		cout<< "Error...not an irrational number" << endl;
	}
}

string Number::getType(){
	return sType;
}

string Irrational::toString(){
	return "aaa";
}

float Number::getValue(){
	return fValue;
}

Number Irrational::simplify(){

}
