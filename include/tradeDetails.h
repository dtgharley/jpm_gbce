// tradeDetails.h
//
// Definition of TradeDetails class.
//

#ifndef CLASS_TRADEDETAILS
#define CLASS_TRADEDETAILS

#include <ctime>
#include "defs.h"

class TradeDetails {
public:
	TradeDetails() : code(NULL_CODE), timeStamp(NULL_TIME), quantity(NULL_QUANTITY), buySell(NULL_BYSL), price(NULL_PRICE) {};
	TradeDetails(int cd, time_t ts, int qy, Bysl bs, int pr) : code(cd), timeStamp(ts), quantity(qy), buySell(bs), price(pr) {};
	
	const int code;
	const time_t timeStamp;
        const int quantity;
	const Bysl buySell;
        const int price;
};
#endif

