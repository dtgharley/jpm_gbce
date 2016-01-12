// rsStocks.cpp
//
// Definition of RsStocks class methods.
//

#include "tradeDetails.h"
#include "stock.h"
#include "code.h"
#include "codePrice.h"
#include "rsStocks.h"
#include "defs.h"
#include <boost/format.hpp>

using namespace std;
using namespace boost;

void RsStocks::loop() {
        do {} while(loop_action());
}

bool RsStocks::loop_action() {
        smatch match;
	string input;
	bool quit;
	print_input_message();
	print_input_prompt();
	getline(is, input);
	to_lower(input);
	quit = regex_match(input, quit_pattern);
	if (!quit) {
		if ((regex_match(input, match, request_pattern) && (match.size() > 0))) {
			char m0 = match.str(0)[0];
			switch (m0) {
				case 'd':
					ltCodePrice {
						int dy;
						if (st.cop == Common) {
							dy = (100 * st.lastDividend) / ct.price;
						} else {
							dy = (st.fixedDividend * st.parValue) / ct.price;
						}
						return format("The Dividend Yield for %s at %dp is %d%%") % st.code % ct.price % dy;
					});
					break;
				case 'p':
					ltCodePrice {
						float pe;
						if (st.cop == Common) {
							pe = (float) ct.price / st.lastDividend;
						} else {
							pe = (float) ct.price / ((st.fixedDividend * st.parValue) / 100);
						}
						return format("The Price to Earnings Ratio for %s at %dp is %.2f") % st.code % ct.price % pe;
					});
					break;
				case 'r':
					ltTradeDetails {
						st.trades.push_back(ct);
						string tbs = (ct.buySell == Buy) ? "purchase" : "sale";
						string at = asctime(localtime(&ct.timeStamp));
						return format("Trade recorded for %s of %d %s shares at %dp on %s") % tbs % ct.quantity % st.code % ct.price % at;
					});
					break;
				case 'v':
					ltCode {
						int vwsb = calc_vwi(st);
						return format("The Volume Weighted Stock Price for %s is %dp") % st.code % vwsb;
					});
					break;
				case 'g':
					{
					int slsz = stocks.size();
					int li = 0;
					double ttp = 1.0;
					int apc = 0;
					while (li < slsz) {
						int cvwsb = calc_vwi(stocks.at(li));
						if (cvwsb != 0) {
							ttp *= (double) cvwsb;
							apc++;
						}
						li++;
					}
					double gbce = (apc == 0) ? 0.0 : pow(ttp, (double) 1.0 / (double) apc);	
					endlsFmt(format("The GBCE All Share Index is currently %dp") % (int)gbce);
					break;
					}
			}
		}
	}	
	return !quit;
}
