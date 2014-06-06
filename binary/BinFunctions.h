/*
 * BinFunctions.h
 *
 * Problem #1: Binary Functions
 *
 * 		Author: Bob Timm
 *      GitHub: BajaBob
 *      CSCE 312
 */

#ifndef BINFUNCTIONS_H_
#define BINFUNCTIONS_H_

#include "Gates.h"

class BinFunctions
{

private:

	Gates* g;

public:

	BinFunctions(Gates* gates):g(gates){}


	bool XOR(bool a, bool b)
	{
		bool na = g->Not(a);
		bool nb = g->Not(b);
		bool nab = g->And(na, b);
		bool nba = g->And(nb, a);
		return g->Or(nab, nba);
	}

	bool Mux(bool operation, bool output_if_true, bool output_if_false)
	{
		return g->Or(
					g->And( g->Not(operation), output_if_true),
					g->And( operation, output_if_false));
	}

	bool Sum(bool a, bool b)
	{
		return XOR(a, b);
	}

	bool Sum(bool a, bool b, bool c)
	{
		return Sum(a, Sum(b, c));
	}

	bool CarryOut(bool a, bool b, bool c)
	{
		bool ab = g->And(a, b);
		bool bc = g->And(b, c);
		bool ac = g->And(a, c);
		return g->Or(ab, g->Or(bc, ac));
	}

	bool Equal(bool a, bool b)
	{
		return g->Not(XOR(a, b));
	}

	void test()
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

};



#endif /* BINFUNCTIONS_H_ */
