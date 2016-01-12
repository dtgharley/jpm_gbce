// rsStocksCalc.cpp
//
// Definition of RsStocks class calculation methods.
//

#include "tradeDetails.h"
#include "stock.h"
#include "codePrice.h"
#include "rsStocks.h"
#include "defs.h"

using namespace std;
using namespace boost;

int RsStocks::calc_vwi(const Stock & tstock) {
	int tlsz = tstock.trades.size();
	int li = tlsz - 1;
	long ct = (long)time(0);;
	int ttpq = 0;
	int ttq = 0;
	while (li >= 0) {
		TradeDetails ctd = tstock.trades.at(li);
		long ctt = (long)ctd.timeStamp;
		bool lt15 = (ct - ctt) < (15 * 60 * 1000);
		if (lt15) {
			ttpq += ctd.quantity * ctd.price;
			ttq += ctd.quantity;
			li--;
		} else {
			break;
		}
	}
	int vwsp = ttq == 0 ? 0 : ttpq / ttq;	
	return vwsp;
}


