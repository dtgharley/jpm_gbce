// rsStocksIo.cpp
//
// Definition of RsStocks class IO methods.
//

#include "tradeDetails.h"
#include "stock.h"
#include "code.h"
#include "codePrice.h"
#include "rsStocks.h"
#include "defs.h"
#include <utility>

using namespace std;
using namespace boost;

void RsStocks::print_input_message() const {
	os << "Request: D)ividend Yield" << endl;
	os << "         P)E Ratio" << endl; 
	os << "         R)ecord Trade" << endl;
	os << "         V)olume Weighted Stock Price" << endl;
	os << "         G)BCE All Share Index" << endl;
	os << "or type \"q(uit)\" to terminate the program." << endl;
}
 
void RsStocks::print_input_prompt() const {
	os << "> ";
}

CodePrice RsStocks::read_stock_price() const {
	return readValues<CodePrice>(
		"Please enter the stock code and price.",
		stockprice_pattern,
		stockback_pattern,
		[this](const smatch& mc) {
			string tc = mc["c"];
			to_upper(tc);
			string tp = mc["p"];
			int cc = codeMap.count(tc);
                        if (cc > 0) {
				int cd = codeMap.at(tc);
                                int cp = stoi(tp);
				return pair<bool,CodePrice>(true,CodePrice(cd, cp));
			} else {
				return pair<bool,CodePrice>(false,CodePrice());
			}
		},
		[]() {
			return CodePrice();
		}
	);
}

TradeDetails RsStocks::read_trade_details() const {
	return readValues<TradeDetails>(
		"Please enter either \"Buy\" or \"Sell\" followed by the quantity, and share code followed by \"at\" or \"@\" and the price of the shares required.",
		tradedetails_pattern,
		tradeback_pattern,
		[this](const smatch& mc) {
			string tc = mc["c"];
			to_upper(tc);
			string tq = mc["q"];
			string tb = mc["b"];
			to_lower(tb);
			string tp = mc["p"];
			int cc = codeMap.count(tc);
			if (cc > 0) {
				int cd = codeMap.at(tc);
				time_t ts = time(0);
				int qa = stoi(tq);
				Bysl bs = (tb.compare("buy") == 0) ? Buy : Sell;
				int pr = stoi(tp);
				return pair<bool, TradeDetails>(true,TradeDetails(cd, ts, qa, bs, pr));
			} else { 
				return pair<bool, TradeDetails>(false,TradeDetails());
			}
		},
		[]() {
			return TradeDetails();
		}
	);
}

Code RsStocks::read_stock_code() const {
	return readValues<Code>(
		"Please enter the stock code.",
		stockcode_pattern,
		stockback_pattern,
		[this](const smatch& mc) {
			string tc = mc["c"];
			to_upper(tc);
			int cc = codeMap.count(tc);
                        if (cc > 0) {
				return pair<bool,Code>(true,Code(codeMap.at(tc)));
			} else
				return pair<bool,Code>(false,Code());
		},
		[]() { 
			return Code();
		}
	);
}

