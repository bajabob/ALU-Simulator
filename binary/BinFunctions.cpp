/*
 * BinFunctions.cpp
 *
 * Problem #1: Binary Functions
 *
 * 		Author: Bob Timm
 *      GitHub: BajaBob
 *      CSCE 312
 */

#include "BinFunctions.h"

void BinFunctions::test()
{
	cout << "XOR(1, 1): ";
	g->print( XOR(true, true));

	cout << "XOR(1, 0): ";
	g->print( XOR(true, false));

	cout << "XOR(0, 1): ";
	g->print( XOR(false, true));

	cout << "XOR(0, 0): ";
	g->print( XOR(false, false));

	cout << "Mux(0, 0, 1): ";
	g->print( Mux(false, false, true));

	cout << "Mux(0, 1, 0): ";
	g->print( Mux(false, true, false));

	cout << "Mux(1, 1, 0): ";
	g->print( Mux(true, true, false));

	cout << "Sum(0, 0): ";
	g->print( Sum(false, false));

	cout << "Sum(1, 0): ";
	g->print( Sum(true, false));

	cout << "Sum(1, 1): ";
	g->print( Sum(true, true));

	cout << "Sum(0, 0, 0): ";
	g->print( Sum(false, false, false));

	cout << "Sum(1, 0, 0): ";
	g->print( Sum(true, false, false));

	cout << "Sum(1, 1, 0): ";
	g->print( Sum(true, true, false));

	cout << "Sum(1, 1, 1): ";
	g->print( Sum(true, true, true));

	cout << "CarryOut(0, 0, 0): ";
	g->print( CarryOut(false, false, false));

	cout << "CarryOut(1, 0, 0): ";
	g->print( CarryOut(true, false, false));

	cout << "CarryOut(1, 1, 0): ";
	g->print( CarryOut(true, true, false));

	cout << "CarryOut(1, 1, 1): ";
	g->print( CarryOut(true, true, true));

	cout << "Equal(0, 0): ";
	g->print( Equal(false, false));

	cout << "Equal(1, 0): ";
	g->print( Equal(true, false));

	cout << "Equal(1, 1): ";
	g->print( Equal(true, true));
}
