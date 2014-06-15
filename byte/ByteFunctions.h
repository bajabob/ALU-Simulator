/*
 * BinFunctions.h
 *
 * Problem #2: Byte Functions
 *
 * 		Author: Bob Timm
 *      GitHub: BajaBob
 *      CSCE 312
 */

#ifndef BYTEFUNCTIONS_H_
#define BYTEFUNCTIONS_H_

#include "../binary/Gates.h"
#include "../binary/BinFunctions.h"
#include <cmath>

class ByteFunctions
{

private:

	Gates* g;

	BinFunctions* binf;

	bool zero[8];

public:

	ByteFunctions(Gates* gates, BinFunctions* binFunctions):g(gates), binf(binFunctions){
		zero[0] = false;
		zero[1] = false;
		zero[2] = false;
		zero[3] = false;

		zero[4] = false;
		zero[5] = false;
		zero[6] = false;
		zero[7] = false;
	}

	void CheckForException(bool* byte);

	void ZeroOut(bool* to_zero);
	bool getValue(bool byte[8], int offset);
	void writeValue(bool* byte, int offset, bool value);
	void printValue(bool byte[8]);
	void printValueInDecimal(bool byte[8]);

	bool* Mux(bool* output, bool operation, bool a[8], bool b[8]);
	bool* Addu(bool* output, bool a[8], bool b[8]);
	bool* Negate(bool* output, bool in[8]);
	bool* Subu(bool* output, bool a[8], bool b[8]);
	bool* Add(bool* output, bool a[8], bool b[8]);
	bool* Sub(bool* output, bool a[8], bool b[8]);

	bool* Multu(bool* output, bool a[8], bool b[8]);
	bool* Mult(bool* output, bool a[8], bool b[8]);
	bool* Divu(bool* output, bool a[8], bool b[8]);
	bool* Div(bool* output, bool a[8], bool b[8]);

	bool IsPositive(bool byte[8]);
	bool IsNegative(bool byte[8]);
	bool IsZero(bool byte[8]);
	bool Equal(bool a[8], bool b[8]);
	bool* Equal(bool* output, bool a[8], bool b[8]);
	bool LessThan(bool a[8], bool b[8]);
	bool GreaterThan(bool a[8], bool b[8]);
	bool* LessThan(bool* output, bool a[8], bool b[8]);
	bool* GreaterThan(bool* output, bool a[8], bool b[8]);

	bool* ALU(bool* output, bool instruction[8], bool a[8], bool b[8]);

	bool* And(bool* output, bool a[8], bool b[8]);
	bool* Or(bool* output, bool a[8], bool b[8]);
	bool* ShiftLeft(bool* output, bool a[8]);
	bool* ShiftRight(bool* output, bool a[8]);


	void test();
};


#endif /* BYTEFUNCTIONS_H_ */
