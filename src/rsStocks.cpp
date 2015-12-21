// rsStocks.cpp
//
// Definition of RsStocks class methods.
//

#include "tradeDetails.h"
#include "stock.h"
#include "codePrice.h"
#include "rsStocks.h"
#include "defs.h"
#include <boost/format.hpp>

using namespace std;
using namespace boost;

void RsStocks::init() {
	stocks.push_back(Stock("TEA", Common, 0, NULL_PRICE, 100));
	stocks.push_back(Stock("POP", Common, 8, NULL_PRICE, 100));
	stocks.push_back(Stock("ALE", Common, 23, NULL_PRICE, 60));
	stocks.push_back(Stock("GIN", Preferred, 8, 2, 100));
	stocks.push_back(Stock("JOE", Common, 13, NULL_PRICE, 250));
        for(vector<Stock>::iterator it = stocks.begin(); it < stocks.end(); ++it) {
           codeMap.insert(pair<string,int>(it->code, distance(stocks.begin(), it)));
	}
	quit_pattern = quit_pattern_s;
	request_pattern = request_pattern_s;
	stockprice_pattern = stockprice_pattern_s;
	stockback_pattern = stockback_pattern_s;
	tradedetails_pattern = tradedetails_pattern_s;
	tradeback_pattern = tradeback_pattern_s;
	stockcode_pattern = stockcode_pattern_s;
}	

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
	smatch spm;
	smatch sbm;
	string input;
	bool ok = true;
 	do {
		os << "Please enter the stock code and price." << endl;
		print_input_prompt();
                getline(is, input);
		algorithm::to_lower(input);
                CodePrice cp;
		if ((regex_match(input, spm, stockprice_pattern) && (spm.size() > 0))) {
			string tc = spm["c"];
			algorithm::to_upper(tc);
			string tp = spm["p"];
			int cc = codeMap.count(tc);
                        if (cc > 0) {
				int cd = codeMap.at(tc);
                                int cp = stoi(tp);
				return CodePrice(cd, cp);
			}
		} else { 
			if ((regex_match(input, sbm, stockback_pattern) && (sbm.size() > 0))) {
				return CodePrice();
			}
		}
	} while (ok);
}

TradeDetails RsStocks::read_trade_details() const {
	smatch tdm;
	smatch tbm;
	string input;
	bool ok = true;
	do {
		os << "Please enter either \"Buy\" or \"Sell\" followed by the quantity, and share code followed by \"at\" or \"@\" and the price of the shares required." << endl;
		print_input_prompt();
		getline(is, input);
		algorithm::to_lower(input);
		if ((regex_match(input, tdm, tradedetails_pattern) && (tdm.size() > 0))) {
			string tc = tdm["c"];
			algorithm::to_upper(tc);
			string tq = tdm["q"];
			string tb = tdm["b"];
			algorithm::to_lower(tb);
			string tp = tdm["p"];
			int cc = codeMap.count(tc);
			if (cc > 0) {
				int cd = codeMap.at(tc);
				time_t ts = time(0);
				int qa = stoi(tq);
				Bysl bs = (tb.compare("buy") == 0) ? Buy : Sell;
				int pr = stoi(tp);
				return TradeDetails(cd, ts, qa, bs, pr);
			}
		} else { 
			if ((regex_match(input, tbm, tradeback_pattern) && (tbm.size() > 0))) {
				return TradeDetails();
			}
		}
	} while (ok);
}

int RsStocks::read_stock_code() const {
	smatch scm;
	smatch sbm;
	string input;
	bool ok = true;
 	do {
		os << "Please enter the stock code." << endl;
		print_input_prompt();
                getline(is, input);
		algorithm::to_lower(input);
		if ((regex_match(input, scm, stockcode_pattern) && (scm.size() > 0))) {
			string tc = scm["c"];
			algorithm::to_upper(tc);
			int cc = codeMap.count(tc);
                        if (cc > 0) {
				return codeMap.at(tc);
			}
		} else { 
			if ((regex_match(input, sbm, stockback_pattern) && (sbm.size() > 0))) {
				return NULL_CODE;
			}
		}
	} while (ok);
}

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
	algorithm::to_lower(input);
	quit = regex_match(input, quit_pattern);
	if (!quit) {
		if ((regex_match(input, match, request_pattern) && (match.size() > 0))) {
			char m0 = match.str(0)[0];
			switch (m0) {
				case 'd':
					{
				 	CodePrice cp = read_stock_price();
					if (cp.code != NULL_CODE) {
						Stock& tstock = stocks.at(cp.code);
						int dy;
						if (tstock.cop == Common) {
							dy = (100 * tstock.lastDividend) / cp.price;
						} else {
							dy = (tstock.fixedDividend * tstock.parValue) / cp.price;
						}
						os << endl;
						os << format("The Dividend Yield for %s at %dp is %d%%") % tstock.code % cp.price % dy;
						os << endl << endl;
					}
					break;
					}
				case 'p':
					{
				 	CodePrice cp = read_stock_price();
					if (cp.code != NULL_CODE) {
						Stock& tstock = stocks.at(cp.code);
						float pe;
						if (tstock.cop == Common) {
							pe = (float) cp.price / tstock.lastDividend;
						} else {
							pe = (float) cp.price / ((tstock.fixedDividend * tstock.parValue) / 100);
						}
						os << endl;
						os << format("The Price to Earnings Ratio for %s at %dp is %.2f") % tstock.code % cp.price % pe;
						os << endl << endl;
					}
					}
					break;
				case 'r':
					{
				 	TradeDetails td = read_trade_details();
					if (td.code != NULL_CODE) {
						Stock& tstock = stocks.at(td.code);
						tstock.trades.push_back(td);
						string tbs = (td.buySell == Buy) ? "purchase" : "sale";
						string at = asctime(localtime(&td.timeStamp));
						os << endl;
						os << format("Trade recorded for %s of %d %s shares at %dp on %s") % tbs % td.quantity % tstock.code % td.price % at;
						os << endl << endl;
					}
					break;
					}
				case 'v':
					{
				 	int cd = read_stock_code();
					if (cd != NULL_CODE) {
						Stock& tstock = stocks.at(cd);
						int vwsb = calc_vwi(tstock);
						os << endl;
						os << format("The Volume Weighted Stock Price for %s is %dp") % tstock.code % vwsb;
						os << endl << endl;
					}
					break;
					}
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
					os << endl;
					os << format("The GBCE All Share Index is currently %dp") % (int)gbce;
					os << endl << endl;
					break;
					}
			}
		}
	}	
	return !quit;
}
