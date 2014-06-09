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
			cout << "1" << endl;
		}
		else
		{
			cout << "0" << endl;
		}
	}

	void test();

};

#endif /* GATES_H_ */
