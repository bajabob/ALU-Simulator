/*
 * Gates.h
 *
 *	Logic Gates [AND, OR, NOT]
 *	As well as a few convenience functions for debugging.
 *
 *  Created on: Jun 5, 2014
 *      Author: Bob Timm
 *      GitHub: BajaBob
 *      CSCE 312
 */

#ifndef GATES_H_
#define GATES_H_

#include <iostream>
using namespace std;

class Gates
{

private:

	int functionCount = 0;

public:

	bool And(bool a, bool b)
	{
		functionCount++;
		return a && b;
	}

	bool Or(bool a, bool b)
	{
		functionCount++;
		return a || b;
	}

	bool Not(bool a)
	{
		functionCount++;
		return !a;
	}

	void printFunctionCount()
	{
		cout << "Function Count: " << functionCount << endl;
	}

	void print(bool a)
	{
		if(a)
		{
			cout << "TRUE" << endl;
		}
		else
		{
			cout << "FALSE" << endl;
		}
	}

	void test()
	{
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
	}

};

#endif /* GATES_H_ */
