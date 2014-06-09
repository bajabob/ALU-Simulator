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

public:

	ByteFunctions(Gates* gates, BinFunctions* binFunctions):g(gates), binf(binFunctions){}

	bool getValue(bool byte[8], int offset);
	void writeValue(bool* byte, int offset, bool value);
	void printValue(bool byte[8]);
	void printValueInDecimal(bool byte[8]);

	bool* Mux(bool* output, bool operation, bool a[8], bool b[8]);
	bool* Addu(bool* output, bool a[8], bool b[8]);
	bool* Negate(bool* output, bool in[8]);
	bool* Subu(bool* output, bool a[8], bool b[8]);

	bool IsPositive(bool byte[8]);
	bool IsNegative(bool byte[8]);
	bool IsZero(bool byte[8]);
	bool Equal(bool a[8], bool b[8]);
	bool LessThan(bool a[8], bool b[8]);
	bool GreaterThan(bool a[8], bool b[8]);
	bool* LessThan(bool* output,bool a[8], bool b[8]);
	bool* GreaterThan(bool* output,bool a[8], bool b[8]);

	bool* And(bool* output, bool a[8], bool b[8]);
	bool* Or(bool* output, bool a[8], bool b[8]);
	bool* ShiftLeft(bool* output, bool a[8]);
	bool* ShiftRight(bool* output, bool a[8]);


	void test();
};


#endif /* BYTEFUNCTIONS_H_ */
