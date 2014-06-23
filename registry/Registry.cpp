/*
 * Registry.cpp
 *
 * Problem #6: Registry
 *
 *		Author: Bob Timm
 *      GitHub: BajaBob
 *      CSCE 312
 */

#include "Registry.h"


bool* Registry::getRegistryValue(bool* output, bool address[8])
{
	int i = bytef->getValueInDecimal(address);

	output[0] = registry[i][0];
	output[1] = registry[i][1];
	output[2] = registry[i][2];
	output[3] = registry[i][3];

	output[4] = registry[i][4];
	output[5] = registry[i][5];
	output[6] = registry[i][6];
	output[7] = registry[i][7];

	cout << "Reg(" << i << ") = ";
	bytef->printValue(registry[i]);
	cout << endl;

	return output;
}

bool* Registry::getInstruction(bool* output, bool address[8])
{
	int i = bytef->getValueInDecimal(address);

	output[0] = instructionMemory[i][0];
	output[1] = instructionMemory[i][1];
	output[2] = instructionMemory[i][2];
	output[3] = instructionMemory[i][3];

	output[4] = instructionMemory[i][4];
	output[5] = instructionMemory[i][5];
	output[6] = instructionMemory[i][6];
	output[7] = instructionMemory[i][7];

	cout << "Instruction Memory(" << i << ") = ";
	bytef->printValue(instructionMemory[i]);
	cout << endl;

	return output;
}

void Registry::setRegistryValue(bool address[8], bool value[8])
{
	int i = bytef->getValueInDecimal(address);

	if(i > 15){
		cerr << "Address out of bounds!" << endl;
		return;
	}

	registry[i][0] = value[0];
	registry[i][1] = value[1];
	registry[i][2] = value[2];
	registry[i][3] = value[3];

	registry[i][4] = value[4];
	registry[i][5] = value[5];
	registry[i][6] = value[6];
	registry[i][7] = value[7];

	cout << "Reg(" << i << ") = ";
	bytef->printValue(value);
	cout << endl;
}

void Registry::incrementPC()
{
	bool four[8] = {false, false, false, false, false, true, false, false};

	bytef->Addu(PC, PC, four);
}

void Registry::resetPC()
{
	PC[0] = false;
	PC[1] = false;
	PC[2] = false;
	PC[3] = false;

	PC[4] = false;
	PC[5] = false;
	PC[6] = false;
	PC[7] = false;
}

void Registry::addPC(bool addressOffset[8])
{
	bytef->Addu(PC, PC, addressOffset);
}

void Registry::instructionFetch()
{
	bool t[8];
	bool localOut[8];
	bool four[8] = {false, false, false, false, false, true, false, false};
	getInstruction(localOut, PC);
	IR[0] = localOut[0];
	IR[1] = localOut[1];
	IR[2] = localOut[2];
	IR[3] = localOut[3];

	IR[4] = localOut[4];
	IR[5] = localOut[5];
	IR[6] = localOut[6];
	IR[7] = localOut[7];

	bytef->Addu(t, four, PC);
	getInstruction(localOut, t);

	IR[8] = localOut[0];
	IR[9] = localOut[1];
	IR[10] = localOut[2];
	IR[11] = localOut[3];

	IR[12] = localOut[4];
	IR[13] = localOut[5];
	IR[14] = localOut[6];
	IR[15] = localOut[7];

	bytef->Addu(t, four, t);
	getInstruction(localOut, t);

	IR[16] = localOut[0];
	IR[17] = localOut[1];
	IR[18] = localOut[2];
	IR[19] = localOut[3];

	IR[20] = localOut[4];
	IR[21] = localOut[5];
	IR[22] = localOut[6];
	IR[23] = localOut[7];

	bytef->Addu(t, four, t);
	getInstruction(localOut, t);

	IR[24] = localOut[0];
	IR[25] = localOut[1];
	IR[26] = localOut[2];
	IR[27] = localOut[3];

	IR[28] = localOut[4];
	IR[29] = localOut[5];
	IR[30] = localOut[6];
	IR[31] = localOut[7];
}


void Registry::instructionDecode()
{
	// load op
	op[0] = IR[0];
	op[1] = IR[1];
	op[2] = IR[2];
	op[3] = IR[3];

	op[4] = IR[4];
	op[5] = IR[5];
	op[6] = IR[6];
	op[7] = IR[7];

	// load rs
	rs[0] = IR[8];
	rs[1] = IR[9];
	rs[2] = IR[10];
	rs[3] = IR[11];

	rs[4] = IR[12];
	rs[5] = IR[13];
	rs[6] = IR[14];
	rs[7] = IR[15];
	// load values in reg to rs
	getRegistryValue(rs, rs);

	rt[0] = IR[16];
	rt[1] = IR[17];
	rt[2] = IR[18];
	rt[3] = IR[19];

	rt[4] = IR[20];
	rt[5] = IR[21];
	rt[6] = IR[22];
	rt[7] = IR[23];
	// load values in reg to rt
	getRegistryValue(rt, rt);

	// load rd
	rd[0] = IR[24];
	rd[1] = IR[25];
	rd[2] = IR[26];
	rd[3] = IR[27];

	rd[4] = IR[28];
	rd[5] = IR[29];
	rd[6] = IR[30];
	rd[7] = IR[31];
}

void Registry::execution()
{
	bytef->ZeroOut(exeResult);
	bytef->ALU(exeResult, op, rs, rt);
}

void Registry::store()
{
	bool lw[8] = {false, false, false, false, true, true, true, false};
	if(bytef->Equal(op, lw))
	{
		mem(rd, rs, true, false);
	}

	bool sw[8] = {false, false, false, false, true, true, true, true};
	if(bytef->Equal(op, sw))
	{
		mem(rs, rd, false, true);
	}
}

void Registry::writeback()
{
	int reg = bytef->getValueInDecimal(rd);

	registry[reg][0] = exeResult[0];
	registry[reg][1] = exeResult[1];
	registry[reg][2] = exeResult[2];
	registry[reg][3] = exeResult[3];

	registry[reg][4] = exeResult[4];
	registry[reg][5] = exeResult[5];
	registry[reg][6] = exeResult[6];
	registry[reg][7] = exeResult[7];
}


/**
 * Call using -> ifstream ifs ("some_code.txt");
 */
void Registry::initializeInstructionMemory(ifstream& fp)
{

	for(int i = 0; i < 256; ++i)
	{
		instructionMemory[i][0] = false;
		instructionMemory[i][1] = false;
		instructionMemory[i][2] = false;
		instructionMemory[i][3] = false;

		instructionMemory[i][4] = false;
		instructionMemory[i][5] = false;
		instructionMemory[i][6] = false;
		instructionMemory[i][7] = false;
	}

	cout << "Reading to instructions memory..." << endl;

	int iCount = 0;
	try
	{
		string line;
		while(getline(fp, line))
		{
			vector<string> result = explode(line, ' ');
			cout.width(5);
			cout << iCount + 1;
			for (size_t i = 0; i < result.size(); i++) {
				cout << "  " << result[i];
			}
			cout << endl;

			bool inst[8];
			getInstructionValue(inst, result[0]);
			instructionMemory[iCount * 4][0] = inst[0];
			instructionMemory[iCount * 4][1] = inst[1];
			instructionMemory[iCount * 4][2] = inst[2];
			instructionMemory[iCount * 4][3] = inst[3];

			instructionMemory[iCount * 4][4] = inst[4];
			instructionMemory[iCount * 4][5] = inst[5];
			instructionMemory[iCount * 4][6] = inst[6];
			instructionMemory[iCount * 4][7] = inst[7];

			bytef->printValue(instructionMemory[iCount*4]);
			cout << " ";

			bytef->stringToByte(instructionMemory[iCount * 4 + 1], result[1]);
			bytef->printValue(instructionMemory[iCount*4 + 1]);
			cout << " ";

			bytef->stringToByte(instructionMemory[iCount * 4 + 2], result[2]);
			bytef->printValue(instructionMemory[iCount*4 + 2]);
			cout << " ";

			bytef->stringToByte(instructionMemory[iCount * 4 + 3], result[3]);
			bytef->printValue(instructionMemory[iCount*4 + 3]);
			cout << endl;

			iCount++;

			if(fp.eof())
			{ // EOF? Break.
				fp.close();
				break;
			}
		}
	}
	catch(string& s)
	{
        cout << "Error message: " << s << endl;
    }
}

/**
 * Using for parsing instruction files
 * usage:
 *
 * string blah = "___this_ is__ th_e str__ing we__ will use__";
   vector<string> result = explode(blah, '_');

    for (size_t i = 0; i < result.size(); i++) {
        cout << "\"" << result[i] << "\"" << endl;
    }
 */
vector<string> Registry::explode(const string& str, const char& ch) {
    string next;
    vector<string> result;

    // For each character in the string
    for (string::const_iterator it = str.begin(); it != str.end(); it++) {
        // If we've hit the terminal character
        if (*it == ch) {
            // If we have some characters accumulated
            if (!next.empty()) {
                // Add them to the result vector
                result.push_back(next);
                next.clear();
            }
        } else {
            // Accumulate the next character into the sequence
            next += *it;
        }
    }
    if (!next.empty())
         result.push_back(next);
    return result;
}


bool* Registry::getInstructionValue(bool* output, string instructionName)
{
	bytef->ZeroOut(output);
	if(!instructionName.compare("ADDU"))
	{
		output[3] = true;
	}
	if(!instructionName.compare("SUBU"))
	{
		output[3] = true;
		output[7] = true;
	}
	if(!instructionName.compare("NEG"))
	{
		output[6] = true;
	}
	if(!instructionName.compare("EQ"))
	{
		output[6] = true;
		output[7] = true;
	}
	if(!instructionName.compare("LT"))
	{
		output[5] = true;
	}
	if(!instructionName.compare("GT"))
	{
		output[5] = true;
		output[7] = true;
	}
	if(!instructionName.compare("AND"))
	{
		output[5] = true;
		output[6] = true;
	}
	if(!instructionName.compare("OR"))
	{
		output[5] = true;
		output[6] = true;
		output[7] = true;
	}
	if(!instructionName.compare("SLL"))
	{
		output[4] = true;
	}
	if(!instructionName.compare("SRL"))
	{
		output[4] = true;
		output[7] = true;
	}
	if(!instructionName.compare("ADD"))
	{
		// intentionally blank
	}
	if(!instructionName.compare("SUB"))
	{
		output[7] = true;
	}
	if(!instructionName.compare("MULTU"))
	{
		output[4] = true;
		output[6] = true;
	}
	if(!instructionName.compare("MULT"))
	{
		output[4] = true;
		output[6] = true;
		output[7] = true;
	}
	if(!instructionName.compare("DIVU"))
	{
		output[4] = true;
		output[5] = true;
	}
	if(!instructionName.compare("DIV"))
	{
		output[4] = true;
		output[5] = true;
		output[7] = true;
	}
	if(!instructionName.compare("LW"))
	{
		output[4] = true;
		output[5] = true;
		output[6] = true;
	}
	if(!instructionName.compare("SW"))
	{
		output[4] = true;
		output[5] = true;
		output[6] = true;
		output[7] = true;
	}
	return output;
}

void Registry::mem(bool registrylocation[8], bool memlocation[16], bool read, bool write)
{
	if(read)
	{
		lw(registrylocation, memlocation);
	}
	if(write)
	{
		sw(registrylocation, memlocation);
	}
}

void Registry::lw(bool registrylocation[8], bool memlocation[8])
{
	int reg = bytef->getValueInDecimal(registrylocation);
	int mem = bytef->getValueInDecimal(memlocation);

	registry[reg][0] = dataMemory[mem][0];
	registry[reg][1] = dataMemory[mem][1];
	registry[reg][2] = dataMemory[mem][2];
	registry[reg][3] = dataMemory[mem][3];

	registry[reg][4] = dataMemory[mem][4];
	registry[reg][5] = dataMemory[mem][5];
	registry[reg][6] = dataMemory[mem][6];
	registry[reg][7] = dataMemory[mem][7];
}

void Registry::sw(bool registrylocation[8], bool memlocation[8])
{
	int reg = bytef->getValueInDecimal(registrylocation);
	int mem = bytef->getValueInDecimal(memlocation);

	dataMemory[mem][0] = registry[reg][0];
	dataMemory[mem][1] = registry[reg][1];
	dataMemory[mem][2] = registry[reg][2];
	dataMemory[mem][3] = registry[reg][3];

	dataMemory[mem][4] = registry[reg][4];
	dataMemory[mem][5] = registry[reg][5];
	dataMemory[mem][6] = registry[reg][6];
	dataMemory[mem][7] = registry[reg][7];
}

void Registry::test()
{
	cout << "Registry Functions" << endl;

	bool output[8];

	bool b1[8] = {false, false, false, false, false, false, true, true};
	bool b2[8] = {false, false, false, false, true, true, false, false};

	cout << "Test Value B1 Binary: ";
	bytef->printValue(b1);
	cout << " Decimal: ";
	bytef->printValueInDecimal(b1);
	cout << endl;

	cout << "Test Value B2 Binary: ";
	bytef->printValue(b2);
	cout << " Decimal: ";
	bytef->printValueInDecimal(b2);
	cout << endl;

	cout << "getRegistryValue(B1): " << endl;
	getRegistryValue(output, b1);

	cout << "setRegistryValue(B1, B2): " << endl;
	setRegistryValue(b1, b2);

	cout << "getRegistryValue(B1): " << endl;
	getRegistryValue(output, b1);
	cout << endl << endl;

	cout << "resetPC()" << endl;
	cout << "incrementPC()" << endl;
	incrementPC();
	bytef->printValue(PC);
	cout << " / ";
	bytef->printValueInDecimal(PC);
	cout << endl << "addPC(B2)" << endl;
	addPC(b2);
	bytef->printValue(PC);
	cout << " / ";
	bytef->printValueInDecimal(PC);
	cout << endl;

	cout << "getInstructionValue(\"ADD\"): ";
	bytef->printValue(getInstructionValue(output, "ADD"));
	cout << endl;

	cout << "getInstructionValue(\"NEG\"): ";
	bytef->printValue(getInstructionValue(output, "NEG"));
	cout << endl;

	string file = "instruction_tests/test1.txt";
	ifstream ifs(file);
	cout << file << endl;
	initializeInstructionMemory(ifs);


}
