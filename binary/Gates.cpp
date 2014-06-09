/*
 * Gates.cpp
 *
 *	Logic Gates [AND, OR, NOT]
 *	As well as a few convenience functions for debugging.
 *
 *  Created on: Jun 5, 2014
 *      Author: Bob Timm
 *      GitHub: BajaBob
 *      CSCE 312
 */

#include "Gates.h"

void Gates::test()
{
	cout << "Gate Functions" << endl;

	cout << "And(1, 0): ";
	print( And(true, false));

	cout << "And(1, 1): ";
	print( And(true, true));

	cout << "And(0, 0): ";
	print( And(false, false));

	cout << "Or(0, 0): ";
	print( Or(false, false));

	cout << "Or(1, 0): ";
	print( Or(true, false));

	cout << "Or(1, 1): ";
	print( Or(true, true));

	cout << "Not(1): ";
	print( Not(true));

	cout << "Not(0): ";
	print( Not(false));

	cout << "Should equal total # of calls above: " << endl;
	printFunctionCount();

	cout << endl << endl;
}

