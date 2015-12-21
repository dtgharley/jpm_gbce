// rsStocks.h
//
// Definition of RsStocks class.
//

#ifndef CLASS_RSSTOCKS
#define CLASS_RSSTOCKS

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

using namespace std;
using namespace boost;

typedef map<string, int> CodeMap;

class RsStocks {
	friend class RsST;
public:
	RsStocks() : is(cin), os(cout) {this->init();};
	void loop();
private:
	RsStocks(istream &i, ostream &o) : is(i), os(o) {this->init();};

	void init();
	istream &is;
        ostream &os;

	bool loop_action();
	void print_input_message() const;
	void print_input_prompt() const;
        CodePrice read_stock_price() const;
	TradeDetails read_trade_details() const;
	int read_stock_code() const;
	int calc_vwi(const Stock &tstock);

	vector<Stock> stocks;
	CodeMap codeMap;

	regex quit_pattern;
	const string quit_pattern_s = "q(uit)*";
	regex request_pattern; 
	const string request_pattern_s = "[dprvg]"; 
	regex stockprice_pattern; 
	const string stockprice_pattern_s = "(?<c>[a-z]{3}+)\\s*(?<p>\\d{1,5}+)p?"; 
	regex stockback_pattern; 
	const string stockback_pattern_s = "b(ack)*"; 
	regex tradedetails_pattern; 
	const string tradedetails_pattern_s = "(?<b>(buy|sell))\\s*(?<q>\\d{1,5})\\s*(?<c>[a-z]{3}+)\\s*(at|@)\\s*(?<p>\\d{1,5})p?"; 
	regex tradeback_pattern; 
	const string tradeback_pattern_s = "b(ack)*"; 
	regex stockcode_pattern; 
	const string stockcode_pattern_s = "(?<c>[a-z]{3}+)"; 
};
#endif

