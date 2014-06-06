/*
 * ByteFunctions.h
 *
 *  Created on: Jun 6, 2014
 *      Author: bob
 */

#ifndef BYTEFUNCTIONS_H_
#define BYTEFUNCTIONS_H_

#include "../binary/Gates.h"

class ByteFunctions
{

private:

	Gates* g;

public:

	ByteFunctions(Gates* gates):g(gates){}

	bool getValue(bool byte[8], int offset);

};


#endif /* BYTEFUNCTIONS_H_ */
