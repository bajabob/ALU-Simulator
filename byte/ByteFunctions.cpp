/*
 * BinFunctions.cpp
 *
 * Problem #2: Byte Functions
 *
 * 		Author: Bob Timm
 *      GitHub: BajaBob
 *      CSCE 312
 */

#include "ByteFunctions.h"

bool ByteFunctions::getValue(bool byte[8], int offset)
{
	if(offset > 7 || offset < 0)
		cerr << "Specified offset out of range" << endl;
	else
		return byte[offset];
	return false;
}
void ByteFunctions::writeValue(bool* byte, int offset, bool value)
{
	if(offset > 7 || offset < 0)
		cerr << "Specified offset out of range" << endl;
	else
		byte[offset] = value;
}
void ByteFunctions::printValue(bool byte[8])
{
	for(int i = 0; i < 8; ++i)
		cout << getValue(byte, i);
}
void ByteFunctions::printValueInDecimal(bool byte[8])
{
	int total = 0;
	for(int i = 0; i < 8; ++i)
	{
		if(getValue(byte, i)){
			total += pow(2, 7-i);
		}
	}
	cout << total;
}


void ByteFunctions::test()
{
	bool byte[8] = {true, false, true, false, true, false, true, false};
	printValue(byte);
	cout << " to decimal: ";
	printValueInDecimal(byte);
	cout << endl;

	writeValue(byte, 1, true);
	writeValue(byte, 7, true);
	printValue(byte);
	cout << " to decimal: ";
	printValueInDecimal(byte);
	cout << endl;
}
