// code.h
//
// Definition of Code class.
//

#ifndef CLASS_CODE
#define CLASS_CODE

#include "defs.h"

class Code {
public:
	Code() : code(NULL_CODE) {};
        Code(int cd) : code(cd) {};
	const int code;
};
#endif

