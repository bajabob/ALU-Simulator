/*
 * Test.cpp
 *
 *  Created on: Jun 5, 2014
 *      Author: bob
 */

#include <iostream>
#include "binary/Gates.h"
#include "binary/BinFunctions.h"

using namespace std;

int main()
{
	Gates g;
	BinFunctions bf( &g );

	/**
	 * Test Gate Functions
	 */
	g.test();

	/**
	 * Test Binary Functions
	 */
	bf.test();
}
