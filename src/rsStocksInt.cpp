// rsStocksInt.cpp
//
// Definition of RsStocks class internal/utility methods.
//

#include "rsStocks.h"
#include "defs.h"
#include "ext.h"
#include <utility>

using namespace std;
using namespace boost;

void RsStocks::init() {
	vector<Stock> ts = {{"TEA", Common, 0, NULL_PRICE, 100},
			    {"POP", Common, 8, NULL_PRICE, 100},
			    {"ALE", Common, 23, NULL_PRICE, 60},
			    {"GIN", Preferred, 8, 2, 100},
			    {"JOE", Common, 13, NULL_PRICE, 250}};
        for_each_indexed(ts.begin(), ts.end(), [this](unsigned ix, const Stock &it) {
		stocks.push_back(it);
		codeMap.insert(pair<string,int>(it.code, ix));
	});
}	

void RsStocks::endlsFmt(const fstring& fmt) const {
	os << endl;
	os << fmt;
	os << endl << endl;
}

