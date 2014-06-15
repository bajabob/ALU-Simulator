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
					g->And( g->Not(operation), output_if_false),
					g->And( operation, output_if_true));
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

	void test();

};



#endif /* BINFUNCTIONS_H_ */
