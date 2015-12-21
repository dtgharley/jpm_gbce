// stock.h
//
// Definition of Stock class.
//

#ifndef CLASS_STOCK
#define CLASS_STOCK

#include <boost/algorithm/string.hpp>
#include <vector>
#include "tradeDetails.h"
#include "defs.h"

using namespace std;
using namespace boost;

class Stock {
public:
        Stock(string cd, Cmpf cp, int ld, int fd, int pv) : code(cd), cop(cp), lastDividend(ld), fixedDividend(fd), parValue(pv) {};
        
	const string code;
	const Cmpf cop;
	const int lastDividend;
	const int fixedDividend;
	const int parValue;
        vector<TradeDetails> trades;
};

#endif
