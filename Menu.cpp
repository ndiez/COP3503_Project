#include <iostream>
#include <stdexcept>
#include "Operations.h"
#include "Shunting.h"
#include "Number.h"
#include "Irrational.h"
#include "Rational.h"

using namespace std;
int main() {
	Number* ans = new Rational(0);
	Number* ansOld = new Rational(0);
	Shunting* s = new Shunting();
	int computeLoop = 1;
	int helpLoop = 0;
	int reviewLoop = 0;
	string computeInput, helpInput, reviewInput, expressionOld;
	cout << "------------------------------------------------------------------------------" << endl;
	cout << "Expression Calculator Project"													 << endl;
	cout << "By: Yayati Bagga, Nick Diez, Kayleigh Dvorak, Mathew Giaramita"		 		 << endl;
	cout << "!!! WARNING !!! Include negative numbers first."								 << endl;
	cout << "Example: 5 * -12 -----> -12 * 5"															 << endl;
	cout << "!!! WARNING !!! Include a space between each operation of the following type:"  << endl;
	cout << "+, -, *, /, ^." 																 << endl;
	cout << "------------------------------------------------------------------------------" << endl;
	cout << endl;
	while (computeLoop == 1) {
		cout << "Enter an expression to compute, menu commands are: " 					 	 << endl;
		cout << "Help, Float, Review, Quit" 														 << endl;
		cout << endl;
		cout << "Enter an expression or an option from the menu:" 							 << endl;
		cin.clear();
		computeInput.clear();
		getline(cin, computeInput);
		if (computeInput == "") {
			cout << "Nothing here to check.." << endl;
		}
		else if (computeInput.at(0) == 'H' || 
				 computeInput.at(0) == 'h') {
			cout << "Entering help menu..." << endl;
			helpLoop = 1;
			while (helpLoop == 1) {
				cout << string(4, '\n');
				cout << "------------------------------------------------------------------------------" << endl;
				cout << "1. Formatting Expressions"														 << endl;
				cout << "2. Review Mode Help"															 << endl;
				cout << "3. Credit List"																 << endl;
				cout << "4. Back to Compute"															 << endl;
				cout << "5. Quit"																		 << endl;
				cout << "------------------------------------------------------------------------------" << endl;
				cout << "Enter an option from the menu:"												 << endl;
				cin >> helpInput;
				if (helpInput.at(0) == '1' ||
					helpInput.at(0) == 'F' ||
					helpInput.at(0) == 'f' ) {
					cout << "------------------------------------------------------------------------------" << endl;
					cout << "Expression Format Help Menu:" 													 << endl;
					cout << "Add: \'x + y\' where x and y are either rational or irrational numbers."        << endl;
					cout << "Subtract: \'x - y\' where x and y are either rational or irrational numbers."   << endl;
					cout << "Multiply: \'x * y\' where x and y are either rational or irrational numbers." 	 << endl;
					cout << "Divide: \'x / y\' where x and y are either rational or irrational numbers." 	 << endl;
					cout << "Exponent: \'x ^ y\' where x and y are either rational or irrational numbers." 	 << endl;
					cout << "Nth Root: \'xrt:y' where x and y are either rational or irrational numbers." 	 << endl;
					cout << "Square Root: \'sqrt:x\' where x is either a rational or irrational number."     << endl;
					cout << "Log Base: \'log_y:x\' where x and y are either rational or irrational numbers." << endl;
					cout << "Negative Numbers: \'(-x)\' Add parenthesis outside of number." << endl;
					cout << "Valid irrational numbers are pi and e."										 << endl;
					cout << "------------------------------------------------------------------------------" << endl;
				}
				else if (helpInput.at(0) == '2' ||
						 helpInput.at(0) == 'R' ||
						 helpInput.at(0) == 'r' ) {
					cout << "------------------------------------------------------------------------------" << endl;
					cout << "Review mode allows the user to look back at the last expression entered and "   << endl;
					cout << "also gives the user an option to view a floating point representation of the"   << endl;
					cout << "previous result. Additionally, there is an option to set \"ans\" to the value"  << endl;
					cout << "of the previous result if the user wishes." 									 << endl;
					cout << "------------------------------------------------------------------------------" << endl;
				}
				else if (helpInput.at(0) == '3' ||
						 helpInput.at(0) == 'C' ||
						 helpInput.at(0) == 'c' ) {
					cout << "------------------------------------------------------------------------------" << endl;
					cout << "Nick Diez: 		Menu and Operations" 										 << endl;
					cout << "Mathew Giaramita: 	Operations and Irrational" 									 << endl;
					cout << "Kayleigh Dvorak: 	Shunting and Rational" 										 << endl;
					cout << "Freddy Jimenez:  	Nothing" 													 << endl;
					cout << "Yayati Bagga: 		Shunting" 													 << endl;
					cout << "------------------------------------------------------------------------------" << endl;
				}
				else if (helpInput.at(0) == '4' ||
						 helpInput.at(0) == 'B' ||
						 helpInput.at(0) == 'b' ) {
					cout << "Going back..." << endl;
					helpLoop = 0;
				}
				else if (helpInput.at(0) == '5' ||
						 helpInput.at(0) == 'Q' ||
						 helpInput.at(0) == 'q' ) {
					cout << "Quitting..." << endl;
					helpLoop = 0;
					computeLoop = 0;
				}
			}
		}
		else if (computeInput.at(0) == 'R' || 
				 computeInput.at(0) == 'r') {
			cout << "Entering review mode..." << endl;
			reviewLoop = 1;
			while (reviewLoop == 1) {
				cout << string(5, '\n');
				cout << "------------------------------------------------------------------------------" << endl;
				cout << "1. View Previous Expression"													 << endl;
				cout << "2. Floating Point of Last Answer"												 << endl;
				cout << "3. Set ans to Previous Answer"													 << endl;
				cout << "4. Back to Compute"															 << endl;
				cout << "5. Quit"																		 << endl;
				cout << "------------------------------------------------------------------------------" << endl;
				cout << "Enter an option from the menu:"								 				 << endl;
				cin >> reviewInput;
				if (reviewInput.at(0) == '1' ||
					reviewInput.at(0) == 'V' ||
					reviewInput.at(0) == 'v') {
					cout << "The previous expression was:" << endl;
					cout << expressionOld << endl;
					cout << "Return to compute mode?" << endl;
					cin >> reviewInput;
					if (reviewInput.at(0) == 'Y' ||
						reviewInput.at(0) == 'y') {
						cout << "Going back..." << endl;
						reviewLoop = 0;
					}
					else {
						cout << "Resetting review menu..." << endl;
					}
				}
				else if (reviewInput.at(0) == '2' ||
						 reviewInput.at(0) == 'F' ||
						 reviewInput.at(0) == 'f') {
					cout << "The floating point of the previous answer is:" << endl;
					cout << ans->getValue() << endl;
					cout << "Return to computing mode?" << endl;
					cin >> reviewInput;
					if (reviewInput.at(0) == 'Y' ||
						reviewInput.at(0) == 'y') {
						cout << "Going back..." << endl;
						reviewLoop = 0;
					}
					else {
						cout << "Resetting review menu..." << endl;
					}	
				}
				else if (reviewInput.at(0) == '3' ||
						 reviewInput.at(0) == 'S' ||
						 reviewInput.at(0) == 's') {
					cout << "Setting ans to previous answer..." << endl;
					// HOAX, previous answer already set to ans HA
					cout << "Previous answer stored in ans, return to compute mode?" << endl;
					cin >> reviewInput;
					if (reviewInput.at(0) == 'Y' ||
						reviewInput.at(0) == 'y') {
						cout << "Going back..." << endl;
						reviewLoop = 0;
					}
					else {
						cout << "Resetting review menu..." << endl;
					}
				}
				else if (reviewInput.at(0) == '4' ||
						 reviewInput.at(0) == 'B' ||
						 reviewInput.at(0) == 'b') {
					cout << "Going back..." << endl;
					reviewLoop = 0;
				}
				else if (reviewInput.at(0) == '5' ||
						 reviewInput.at(0) == 'Q' ||
						 reviewInput.at(0) == 'q') {
					cout << "Quitting..." << endl;
					reviewLoop = 0;
					computeLoop = 0;
				}
			}
		}
		else if (computeInput.at(0) == 'Q' || 
				 computeInput.at(0) == 'q') {
			cout << "Quitting..." << endl;
			computeLoop = 0;
		}
		else if (computeInput.at(0) == '0' ||
				 computeInput.at(0) == '1' ||
				 computeInput.at(0) == '2' ||
				 computeInput.at(0) == '3' ||
				 computeInput.at(0) == '4' ||
				 computeInput.at(0) == '5' ||
				 computeInput.at(0) == '6' ||
				 computeInput.at(0) == '7' ||
				 computeInput.at(0) == '8' ||
				 computeInput.at(0) == '9' ||
				 computeInput.at(0) == '-' ||
				 computeInput.at(0) == 'a' ||
				 computeInput.at(0) == '(' || 
				 computeInput.at(0) == 'p' ||
				 computeInput.at(0) == 'e' ||
				 computeInput.at(0) == 'l' ||
				 computeInput.at(0) == '.' ||
				 computeInput.at(0) == 's' ) {
				expressionOld = computeInput;
				cin.clear();
				ans = s->evaluate(computeInput, ansOld);
				ansOld = ans;
				if(ans->getType() == "Rational")
					cout << "The result of your expression is: " << ans->toString() << endl;
				else
					cout << "The result of your expression is: " << ans->toString().substr(0, ans->toString().length() - 4) << endl;
				computeInput.clear();
		}
		else if (computeInput.at(0) == 'F' ||
				 computeInput.at(0) == 'f') {
			cout << "The floating point of the previous answer is:" << endl;
			cout << ans->getValue() << endl;
		}
		else {
			cout << "Invalid expression..." << endl;
		}
	}
}
