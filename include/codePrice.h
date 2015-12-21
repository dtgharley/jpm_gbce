// codePrice.h
//
// Definition of CodePrice class.
//

#ifndef CLASS_CODEPRICE
#define CLASS_CODEPRICE

#include "defs.h"

class CodePrice {
public:
	CodePrice() : code(NULL_CODE), price(NULL_PRICE) {};
        CodePrice(int cd, int pr) : code(cd), price(pr) {};
	const int code;
        const int price;
};
#endif

