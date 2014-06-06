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

using namespace std;

int main()
{
	Gates g;
	BinFunctions binf( &g );
	ByteFunctions bytef ( &g );


	/**
	 * Test Gate Functions
	 */
	g.test();

	/**
	 * Test Binary Functions
	 */
	binf.test();

	/**
	 * Test Byte Functions
	 */
	bytef.test();
}
