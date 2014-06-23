/*
 * Test.cpp
 *
 * Test all functions and gate logic. Over time this file will
 * adopt a menu for additional functonality.
 *
 *  Created on: Jun 5, 2014
 *      Author: Bob Timm
 *      GitHub: BajaBob
 *      CSCE 312
 */

#include <iostream>
#include "binary/Gates.h"
#include "binary/BinFunctions.h"
#include "byte/ByteFunctions.h"
#include "registry/Registry.h"

using namespace std;

int main()
{
	Gates g;
	BinFunctions binf( &g );
	ByteFunctions bytef ( &g, &binf );
	Registry reg(&g, &binf, &bytef);


	/**
	 * Test Gate Functions
	 */
	cout << endl << endl;
	g.test();

	/**
	 * Test Binary Functions
	 */
	binf.test();

	/**
	 * Test Byte Functions
	 */
	bytef.test();

	/**
	 * Test Reg Functions
	 */
	reg.test();
}
