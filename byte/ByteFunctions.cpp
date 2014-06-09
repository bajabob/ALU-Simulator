/*
 * BinFunctions.cpp
 *
 * Problem #2: Byte Functions
 *
 *		Author: Bob Timm
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

bool* ByteFunctions::Mux(bool* output, bool operation, bool a[8], bool b[8])
{
	output[0] = binf->Mux(operation, a[0], b[0]);
	output[1] = binf->Mux(operation, a[1], b[1]);
	output[2] = binf->Mux(operation, a[2], b[2]);
	output[3] = binf->Mux(operation, a[3], b[3]);

	output[4] = binf->Mux(operation, a[4], b[4]);
	output[5] = binf->Mux(operation, a[5], b[5]);
	output[6] = binf->Mux(operation, a[6], b[6]);
	output[7] = binf->Mux(operation, a[7], b[7]);

	return output;
}

bool* ByteFunctions::Addu(bool* output, bool a[8], bool b[8])
{
	bool s7 = binf->Sum(a[7], b[7], false);
	bool c7 = binf->CarryOut(a[7], b[7], false);
	bool s6 = binf->Sum(a[6], b[6], c7);
	bool c6 = binf->CarryOut(a[6], b[6], c7);

	bool s5 = binf->Sum(a[5], b[5], c6);
	bool c5 = binf->CarryOut(a[5], b[5], c6);
	bool s4 = binf->Sum(a[4], b[4], c5);
	bool c4 = binf->CarryOut(a[4], b[4], c5);

	bool s3 = binf->Sum(a[3], b[3], c4);
	bool c3 = binf->CarryOut(a[3], b[3], c4);
	bool s2 = binf->Sum(a[2], b[2], c3);
	bool c2 = binf->CarryOut(a[2], b[2], c3);

	bool s1 = binf->Sum(a[1], b[1], c2);
	bool c1 = binf->CarryOut(a[1], b[1], c2);
	bool s0 = binf->Sum(a[0], b[0], c1);

	output[0] = s0;
	output[1] = s1;
	output[2] = s2;
	output[3] = s3;

	output[4] = s4;
	output[5] = s5;
	output[6] = s6;
	output[7] = s7;

	return output;
}

bool* ByteFunctions::Negate(bool* output, bool in[8])
{
	output[0] = g->Not(in[0]);
	output[1] = g->Not(in[1]);
	output[2] = g->Not(in[2]);
	output[3] = g->Not(in[3]);

	output[4] = g->Not(in[4]);
	output[5] = g->Not(in[5]);
	output[6] = g->Not(in[6]);
	output[7] = g->Not(in[7]);

	bool one[8] = {false, false, false, false, false, false, false, true};

	Addu(output, output, one);

	return output;
}

bool* ByteFunctions::Subu(bool* output, bool a[8], bool b[8])
{
	bool negb[8];
	Negate(negb, b);
	Addu(output, a, negb);
	return output;
}

bool ByteFunctions::IsNegative(bool byte[8])
{
	return g->And(true, byte[0]);
}

bool ByteFunctions::IsPositive(bool byte[8])
{
	return g->And(true, g->Not(byte[0]));
}

bool ByteFunctions::IsZero(bool byte[8])
{
	return g->And(true,
			g->And(g->Not(byte[0]),
					g->And(g->Not(byte[1]),
							g->And(g->Not(byte[2]),
									g->And(g->Not(byte[3]),
											g->And(g->Not(byte[4]),
													g->And(g->Not(byte[5]),
															g->And(g->Not(byte[6]), g->Not(byte))
	)))))));
}

bool ByteFunctions::Equal(bool a[8], bool b[8])
{
	bool diff[8];
	Subu(diff, a, b);

	return IsZero(diff);
}

bool ByteFunctions::LessThan(bool a[8], bool b[8])
{
	bool diff[8];
	Subu(diff, a, b);
	bool rsp = g->Or(IsZero(diff), IsPositive(diff));
	return g->Not(rsp);
}

bool ByteFunctions::GreaterThan(bool a[8], bool b[8])
{
	bool diff[8];
	Subu(diff, a, b);
	bool rsp = g->Or(IsZero(diff), IsNegative(diff));
	return g->Not(rsp);
}

bool* ByteFunctions::LessThan(bool* output,bool a[8], bool b[8])
{
	bool t[8] = {false, false, false, false, false, false, false, true};
	bool f[8] = {false, false, false, false, false, false, false, false};
	return Mux(output, LessThan(a, b), f, t);
}

bool* ByteFunctions::GreaterThan(bool* output,bool a[8], bool b[8])
{
	bool t[8] = {false, false, false, false, false, false, false, true};
	bool f[8] = {false, false, false, false, false, false, false, false};
	return Mux(output, GreaterThan(a, b), f, t);
}

bool* ByteFunctions::And(bool* output, bool a[8], bool b[8])
{
	output[0] = g->And(a[0], b[0]);
	output[1] = g->And(a[1], b[1]);
	output[2] = g->And(a[2], b[2]);
	output[3] = g->And(a[3], b[3]);

	output[4] = g->And(a[4], b[4]);
	output[5] = g->And(a[5], b[5]);
	output[6] = g->And(a[6], b[6]);
	output[7] = g->And(a[7], b[7]);

	return output;
}

bool* ByteFunctions::Or(bool* output, bool a[8], bool b[8])
{
	output[0] = g->Or(a[0], b[0]);
	output[1] = g->Or(a[1], b[1]);
	output[2] = g->Or(a[2], b[2]);
	output[3] = g->Or(a[3], b[3]);

	output[4] = g->Or(a[4], b[4]);
	output[5] = g->Or(a[5], b[5]);
	output[6] = g->Or(a[6], b[6]);
	output[7] = g->Or(a[7], b[7]);

	return output;
}

bool* ByteFunctions::ShiftLeft(bool* output, bool a[8])
{
	output[0] = a[1];
	output[1] = a[2];
	output[2] = a[3];
	output[3] = a[4];

	output[4] = a[5];
	output[5] = a[6];
	output[6] = a[7];
	output[7] = 0;

	return output;
}

bool* ByteFunctions::ShiftRight(bool* output, bool a[8])
{
	output[0] = 0;
	output[1] = a[0];
	output[2] = a[1];
	output[3] = a[2];

	output[4] = a[3];
	output[5] = a[4];
	output[6] = a[5];
	output[7] = a[6];

	return output;
}


void ByteFunctions::test()
{
	cout << "Byte Functions" << endl;

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

	/**
	 * create some random variables to work with
	 */
	bool output[8];
	bool b1[8] = {true, false, true, false, true, false, true, false};
	bool b2[8] = {false, true, false, true, false, true, false, true};
	cout << "Test Values (B1 / B2)" << endl;
	printValue(b1);
	cout << " / ";
	printValue(b2);
	cout << endl;
	printValueInDecimal(b1);
	cout << " / ";
	printValueInDecimal(b2);
	cout << endl;

	cout << "Mux(1, B1, B2): ";
	Mux(output, true, b1, b2);
	printValue(output);
	cout << endl;
	cout << "Mux(0, B1, B2): ";
	Mux(output, false, b1, b2);
	printValue(output);
	cout << endl;

	cout << "Addu(B1, B2): ";
	Addu(output, b1, b2);
	printValue(output);
	cout << endl;

	cout << "Negate(B1): ";
	Negate(output, b1);
	printValue(output);
	cout << endl;

	cout << "Subu(B1, B2): ";
	Subu(output, b1, b2);
	printValue(output);
	cout << endl;

	cout << "Equal(B1, B2): ";
	g->print(Equal(b1, b2));
	cout << "Equal(B1, B1): ";
	g->print(Equal(b1, b1));
	cout << "Equal(B2, B2): ";
	g->print(Equal(b2, b2));

	cout << "LessThan(B1, B2): ";
	g->print(LessThan(b1, b2));
	cout << "LessThan(B2, B1): ";
	g->print(LessThan(b2, b1));

	cout << "GreaterThan(B1, B2): ";
	g->print(GreaterThan(b1, b2));
	cout << "GreaterThan(B2, B1): ";
	g->print(GreaterThan(b2, b1));

	cout << "LessThan(B1, B2): ";
	LessThan(output, b1, b2);
	printValue(output);
	cout << endl;

	cout << "GreaterThan(B1, B2): ";
	GreaterThan(output, b1, b2);
	printValue(output);
	cout << endl;

	cout << "And(B1, B2): ";
	And(output, b1, b2);
	printValue(output);
	cout << endl;
	cout << "And(B1, B1): ";
	And(output, b1, b1);
	printValue(output);
	cout << endl;

	cout << "Or(B1, B2): ";
	Or(output, b1, b2);
	printValue(output);
	cout << endl;
	cout << "Or(B1, B1): ";
	Or(output, b1, b1);
	printValue(output);
	cout << endl;

	cout << "ShiftLeft(B1): ";
	ShiftLeft(output, b1);
	printValue(output);
	cout << endl;
	cout << "In Decimal: ";
	printValueInDecimal(output);
	cout << endl;

	cout << "ShiftRight(B2): ";
	ShiftRight(output, b2);
	printValue(output);
	cout << endl;
	cout << "In Decimal: ";
	printValueInDecimal(output);
	cout << endl;

	cout << endl << endl;
}
