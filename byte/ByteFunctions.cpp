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

void ByteFunctions::ZeroOut(bool* to_zero)
{
	to_zero[0] = false;
	to_zero[1] = false;
	to_zero[2] = false;
	to_zero[3] = false;

	to_zero[4] = false;
	to_zero[5] = false;
	to_zero[6] = false;
	to_zero[7] = false;
}

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

	output[8] = a[8]; // exception bit

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

bool* ByteFunctions::Add(bool* output, bool a[8], bool b[8])
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
	bool c0 = binf->CarryOut(a[0], b[0], c1);

	output[0] = s0;
	output[1] = s1;
	output[2] = s2;
	output[3] = s3;

	output[4] = s4;
	output[5] = s5;
	output[6] = s6;
	output[7] = s7;

	/**
	 * exception bit
	 */
	output[8] = g->Or(g->Not(binf->Equal(c0, c1)), output[8]);

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

bool* ByteFunctions::Sub(bool* output, bool a[8], bool b[8])
{
	bool negb[8];
	Negate(negb, b);
	Add(output, a, negb);
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
															g->And(g->Not(byte[6]), g->Not(byte[7]))
	)))))));
}

bool ByteFunctions::Equal(bool a[8], bool b[8])
{
	bool diff[8];
	Subu(diff, a, b);
	return IsZero(diff);
}

bool* ByteFunctions::Equal(bool* output, bool a[8], bool b[8])
{
	ZeroOut(output);
	output[7] = Equal(a, b);
	return output;
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
	output[7] = a[6];
	output[6] = a[5];
	output[5] = a[4];
	output[4] = a[3];

	output[3] = a[2];
	output[2] = a[1];
	output[1] = a[0];
	output[0] = 0;

	return output;
}


bool* ByteFunctions::Multu(bool* output, bool a[8], bool b[8])
{

	bool ta[8];
	bool tb[8];
	bool temp[8];

	Addu(ta, a, zero);
	Addu(tb, b, zero);

	Mux(output, g->And(tb[7], true), ta, zero);
	ShiftLeft(ta, ta);
	ShiftRight(tb, tb);

	Mux(output, g->And(tb[7], true), Addu(temp, ta, output), output);
	ShiftLeft(ta, ta);
	ShiftRight(tb, tb);

	Mux(output, g->And(tb[7], true), Addu(temp, ta, output), output);
	ShiftLeft(ta, ta);
	ShiftRight(tb, tb);

	Mux(output, g->And(tb[7], true), Addu(temp, ta, output), output);
	ShiftLeft(ta, ta);
	ShiftRight(tb, tb);

	Mux(output, g->And(tb[7], true), Addu(temp, ta, output), output);
	ShiftLeft(ta, ta);
	ShiftRight(tb, tb);

	Mux(output, g->And(tb[7], true), Addu(temp, ta, output), output);
	ShiftLeft(ta, ta);
	ShiftRight(tb, tb);

	Mux(output, g->And(tb[7], true), Addu(temp, ta, output), output);
	ShiftLeft(ta, ta);
	ShiftRight(tb, tb);

	Mux(output, g->And(tb[7], true), Addu(temp, ta, output), output);

	return output;
}

bool* ByteFunctions::Mult(bool* output, bool a[8], bool b[8])
{
	bool ta[8];
	bool tb[8];
	bool temp[8];

	Addu(ta, a, zero);
	Addu(tb, b, zero);

	Mux(output, g->And(tb[7], true), ta, zero);
	ShiftLeft(ta, ta);
	ShiftRight(tb, tb);

	Mux(output, g->And(tb[7], true), Add(temp, ta, output), output);
	ShiftLeft(ta, ta);
	ShiftRight(tb, tb);

	Mux(output, g->And(tb[7], true), Add(temp, ta, output), output);
	ShiftLeft(ta, ta);
	ShiftRight(tb, tb);

	Mux(output, g->And(tb[7], true), Add(temp, ta, output), output);
	ShiftLeft(ta, ta);
	ShiftRight(tb, tb);

	Mux(output, g->And(tb[7], true), Add(temp, ta, output), output);
	ShiftLeft(ta, ta);
	ShiftRight(tb, tb);

	Mux(output, g->And(tb[7], true), Add(temp, ta, output), output);
	ShiftLeft(ta, ta);
	ShiftRight(tb, tb);

	Mux(output, g->And(tb[7], true), Add(temp, ta, output), output);
	ShiftLeft(ta, ta);
	ShiftRight(tb, tb);

	Mux(output, g->And(tb[7], true), Add(temp, ta, output), output);
	return output;
}

/**
 * Instructions not clear on size of input and outputs!
 * Are we supposed to have 16 bit operations? How can we shift
 * by 8 bits when we have only created an 8-bit array? Can not answer
 * with classes that have been created thus far...
 */
bool* ByteFunctions::Divu(bool* output, bool a[8], bool b[8])
{

	bool ta[8];
	bool tb[8];

	Addu(ta, a, zero);
	Addu(tb, b, zero);

	ShiftLeft(tb, tb);
	ShiftLeft(tb, tb);
	ShiftLeft(tb, tb);
	ShiftLeft(tb, tb);

	ShiftLeft(tb, tb);
	ShiftLeft(tb, tb);
	ShiftLeft(tb, tb);
	ShiftLeft(tb, tb);

	// doesn't work. Always returns zero.

	return output;
}

/**
 * Instructions not clear on size of input and outputs!
 * Are we supposed to have 16 bit operations? How can we shift
 * by 8 bits when we have only created an 8-bit array? Can not answer
 * with classes that have been created thus far...
 */
bool* ByteFunctions::Div(bool* output, bool a[8], bool b[8])
{

	return output;
}


bool* ByteFunctions::ALU(bool* output, bool instruction[8], bool a[8], bool b[8])
{
	/**
	 * Each MUX relies on the result of the previous MUX
	 * Doing this allows to pass along the final answer
	 */
	bool temp[8];

	// addu
	bool addu[] = {false, false, false, true, false, false, false, false};
	Mux(output, Equal(instruction, addu), Addu(temp, a, b), output);

	// subu
	bool subu[] = {false, false, false, true, false, false, false, true};
	Mux(output, Equal(instruction, subu), Subu(temp, a, b), output);

	// neg
	bool neg[] = {false, false, false, false, false, false, true, false};
	Mux(output, Equal(instruction, neg), Negate(temp, a), output);

	// equal
	bool eq[] = {false, false, false, false, false, false, true, true};
	Mux(output, Equal(instruction, eq), Equal(temp, a, b), output);

	// less than
	bool lt[] = {false, false, false, false, false, true, false, false};
	Mux(output, Equal(instruction, lt), LessThan(temp, a, b), output);

	// greater than
	bool gt[] = {false, false, false, false, false, true, false, true};
	Mux(output, Equal(instruction, gt), GreaterThan(temp, a, b), output);

	// and
	bool t_and[] = {false, false, false, false, false, true, true, false};
	Mux(output, Equal(instruction, t_and), And(temp, a, b), output);

	// or
	bool t_or[] = {false, false, false, false, false, true, true, true};
	Mux(output, Equal(instruction, t_or), Or(temp, a, b), output);

	// shift left
	bool sll[] = {false, false, false, false, true, false, false, false};
	Mux(output, Equal(instruction, sll), ShiftLeft(temp, a), output);

	// shift right
	bool srl[] = {false, false, false, false, true, false, false, true};
	Mux(output, Equal(instruction, srl), ShiftRight(temp, a), output);

	// add
	bool add[] = {false, false, false, false, false, false, false, false};
	Mux(output, Equal(instruction, add), Add(temp, a, b), output);

	// sub
	bool sub[] = {false, false, false, false, false, false, false, true};
	Mux(output, Equal(instruction, sub), Sub(temp, a, b), output);

	// multu
	bool multu[] = {false, false, false, false, true, false, true, false};
	Mux(output, Equal(instruction, multu), Multu(temp, a, b), output);

	// mult
	bool mult[] = {false, false, false, false, true, false, true, true};
	Mux(output, Equal(instruction, mult), Mult(temp, a, b), output);

	return output;
}

void ByteFunctions::CheckForException(bool* byte)
{
	if(byte[8] == true)
	{
		cerr << "^ ERROR ---> Exception Thrown: Overflow" << endl;
		byte[8] = false;
	}
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
	 * Last bit Index (8) indicates an exception
	 */
	bool output[9];
	output[8] = false;

	/**
	 * create some random variables to work with
	 */
	bool b1[8] = {true, false, true, false, true, false, true, false};
	bool b2[8] = {false, true, false, true, false, true, false, true};
	cout << "Test Value B1: ";
	printValue(b1);
	cout << endl << "Test Value B2: ";
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

	cout << "ALU(ADDU, B1, B2): ";
	bool addu[] = {false, false, false, true, false, false, false, false};
	printValue(ALU(output, addu, b1, b2));
	cout << endl;

	cout << "ALU(SUBU, B1, B2): ";
	bool subu[] = {false, false, false, true, false, false, false, true};
	printValue(ALU(output, subu, b1, b2));
	cout << endl;

	cout << "ALU(NEG, B1): ";
	bool neg[] = {false, false, false, false, false, false, true, false};
	printValue(ALU(output, neg, b1, b2));
	cout << endl;

	cout << "ALU(EQ, B1, B2): ";
	bool eq[] = {false, false, false, false, false, false, true, true};
	printValue(ALU(output, eq, b1, b2));
	cout << endl;
	cout << "ALU(EQ, B1, B1): ";
	printValue(ALU(output, eq, b1, b1));
	cout << endl;

	cout << "ALU(LT, B1, B2): ";
	bool lt[] = {false, false, false, false, false, true, false, false};
	printValue(ALU(output, lt, b1, b2));
	cout << endl;

	cout << "ALU(GT, B1, B2): ";
	bool gt[] = {false, false, false, false, false, true, false, true};
	printValue(ALU(output, gt, b1, b2));
	cout << endl;

	cout << "ALU(AND, B1, B2): ";
	bool t_and[] = {false, false, false, false, false, true, true, false};
	printValue(ALU(output, t_and, b1, b2));
	cout << endl;

	cout << "ALU(OR, B1, B2): ";
	bool t_or[] = {false, false, false, false, false, true, true, true};
	printValue(ALU(output, t_or, b1, b2));
	cout << endl;

	cout << "ALU(SLL, B1, B2): ";
	bool sll[] = {false, false, false, false, true, false, false, false};
	printValue(ALU(output, sll, b1, b2));
	cout << endl;

	cout << "ALU(SRL, B1, B2): ";
	bool srl[] = {false, false, false, false, true, false, false, true};
	printValue(ALU(output, srl, b1, b2));
	cout << endl;

	cout << "ALU(ADD, B1, B2): ";
	bool add[] = {false, false, false, false, false, false, false, false};
	printValue(ALU(output, add, b1, b2));
	cout << endl;
	CheckForException(output);

	bool b3[] = {true, true, true, true, true, true, true, true};
	cout << "Test Value B3: ";
	printValue(b3);
	cout << endl;

	cout << "ALU(ADD, B1, B3): ";
	printValue(ALU(output, add, b1, b3));
	cout << endl;
	CheckForException(output);

	cout << "ALU(SUB, B1, B2): ";
	bool sub[] = {false, false, false, false, false, false, false, true};
	printValue(ALU(output, sub, b1, b2));
	cout << endl;
	CheckForException(output);

	cout << "ALU(SUB, B1, B3): ";
	printValue(ALU(output, sub, b1, b3));
	cout << endl;
	CheckForException(output);

	cout << "ALU(MULTU, B1, B2): ";
	bool multu[] = {false, false, false, false, true, false, true, false};
	printValue(ALU(output, multu, b1, b2));
	cout << endl;

	cout << "ALU(MULT, B1, B2): ";
	bool mult[] = {false, false, false, false, true, false, true, true};
	printValue(ALU(output, mult, b1, b2));
	cout << endl;
	CheckForException(output);

	cout << endl << endl << "Divide functions not completed. Instructions not clear on the use of 16bit arrays. No tools exist to make these functions as of yet!" << endl;

	cout << endl << endl;
}
