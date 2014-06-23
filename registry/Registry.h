/*
 * BinFunctions.h
 *
 * Problem #2: Byte Functions
 *
 * 		Author: Bob Timm
 *      GitHub: BajaBob
 *      CSCE 312
 */

#ifndef REGISTRY_H_
#define REGISTRY_H_

#include "../binary/Gates.h"
#include "../binary/BinFunctions.h"
#include "../byte/ByteFunctions.h"
#include <cmath>
#include <string>
#include <vector>
#include <fstream>

class Registry
{

private:

	Gates* g;

	BinFunctions* binf;

	ByteFunctions* bytef;

	bool op[8], rs[8], rt[8], rd[8], exeResult[8];

	bool registry[16][8];

	bool dataMemory[16][8];

	bool instructionMemory[256][8];

	bool PC[8];

	bool IR[32];

public:

	Registry(Gates* gates, BinFunctions* binFunctions, ByteFunctions* byteFunctions):
		g(gates), binf(binFunctions), bytef(byteFunctions)
	{
		for(int x = 0; x < 16; ++x)
			for(int y = 0; y < 8; ++y)
				registry[x][y] = false;

		resetPC();
	}

	void resetPC();
	void addPC(bool addressOffset[8]);
	void instructionFetch();
	void instructionDecode();
	void execution();
	void store();
	void writeback();

	void initializeInstructionMemory(ifstream& fp);
	vector<string> explode(const string& str, const char& ch);
	bool* getInstructionValue(bool* output, string instructionName);

	void mem(bool registrylocation[8], bool memlocation[8], bool read, bool write);

	void lw(bool registrylocation[8], bool memlocation[8]);
	void sw(bool registrylocation[8], bool memlocation[8]);


	bool* getRegistryValue(bool* output, bool address[8]);
	bool* getInstruction(bool* output, bool address[8]);
	void setRegistryValue(bool address[8], bool value[8]);

	void incrementPC(); // PC = PC + 4

	void test();
};


#endif /* REGISTRY_H_ */
