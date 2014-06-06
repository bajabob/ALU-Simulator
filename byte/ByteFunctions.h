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
#include <cmath>

class ByteFunctions
{

private:

	Gates* g;

public:

	ByteFunctions(Gates* gates):g(gates){}

	bool getValue(bool byte[8], int offset);
	void writeValue(bool* byte, int offset, bool value);
	void printValue(bool byte[8]);
	void printValueInDecimal(bool byte[8]);

	void test();
};


#endif /* BYTEFUNCTIONS_H_ */
