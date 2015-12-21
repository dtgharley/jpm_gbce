// rsStocksT.h
//
// Definition of RsStocksT class.
//

#ifndef CLASS_RSSTOCKSTEST
#define CLASS_RSSTOCKSTEST

#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <map>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <math.h>

#include "tradeDetails.h"
#include "stock.h"
#include "codePrice.h"
#include "rsStocks.h"

using namespace std;
using namespace boost;

#define cp (*cP)
#define td (*tD)

#define BC_CP(m,v) BOOST_CHECK(cp.m == v)
#define BC_TD(m,v) BOOST_CHECK(td.m == v)
#define BC_TD_TR BOOST_CHECK((td.timeStamp >= t0) && (td.timeStamp <= t1))
#define BC_SC(v) BOOST_CHECK(sc == v)
#define BC_VWI(v) BOOST_CHECK(vwi == v)
#define BC_OC(v) BOOST_CHECK(op == v)
#define BC_OT(v,c) BOOST_CHECK(op == (v+lt_ts(c)))

class RsST {
public:
	RsST() : s(RsStocks(this->i, this->o)), cP(nullptr), tD(nullptr), stocks(s.stocks), codeMap(s.codeMap) {};
	
	RsStocks s;
        void read_stock_price() {if (cP != nullptr) delete cP; cP = new CodePrice(s.read_stock_price());};
	void read_stock_price(string ii) {i << ii << endl; read_stock_price();};
	void read_trade_details() {t0 = time(0); if (tD != nullptr) delete tD; tD = new TradeDetails(s.read_trade_details()); t1 = time(0);};
	void read_trade_details(string ii) {i << ii << endl; read_trade_details();};
	void push_trade_details(string ii) {i << ii << endl; read_trade_details(); stocks.at(td.code).trades.push_back(td);};
	void read_stock_code() {sc = s.read_stock_code();};
	void read_stock_code(string ii) {i << ii << endl; read_stock_code();};
	void calc_vwi(const Stock &tstock) {vwi = s.calc_vwi(tstock);};
	void loop() {o.str(""); s.loop_action(); for(int i = 0; i < 9; i++) {string ts = op; getline(o, op); if (ts == "> ") break;}};
	string lt_ts(int i) {string ts = asctime(localtime(&stocks.at(i).trades.back().timeStamp)); trim_right(ts); return ts;}
	stringstream i, o;

	vector<Stock> &stocks;
	CodeMap &codeMap;
	CodePrice *cP;
	TradeDetails *tD;
	time_t t0, t1;
	int sc;
	double vwi;
	string op;
};
#endif

