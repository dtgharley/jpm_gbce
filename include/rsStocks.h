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
#include <functional>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <math.h>

#include "tradeDetails.h"
#include "stock.h"
#include "codePrice.h"
#include "code.h"

using namespace std;
using namespace boost;

typedef boost::basic_format<char> fstring;

typedef map<string, int> CodeMap;

#define wcvFn withCodeValue
#define wcvFnM withCodeValueM

#define wcvPt const Stock&
#define wcvPtM Stock&

#define wcvTemplateDef(FN,PT) template<class T> void FN(T, std::function<fstring(PT, const T&)>)

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

	void endlsFmt(const fstring&) const;
	wcvTemplateDef(wcvFn,wcvPt);
	wcvTemplateDef(wcvFnM,wcvPtM);
	bool loop_action();
	void print_input_message() const;
	void print_input_prompt() const;
	template<class T> T readValues(const string&, const regex&, const regex&, std::function<pair<bool, T>(const smatch&)>, std::function<T ()>) const;
        CodePrice read_stock_price() const;
	TradeDetails read_trade_details() const;
	Code read_stock_code() const;
	int calc_vwi(const Stock &tstock);

	vector<Stock> stocks;
	CodeMap codeMap;

	const regex quit_pattern = regex("q(uit)*");
	const regex request_pattern = regex("[dprvg]"); 
	const regex stockprice_pattern = regex("(?<c>[a-z]{3}+)\\s*(?<p>\\d{1,5}+)p?"); 
	const regex stockback_pattern = regex("b(ack)*"); 
	const regex tradedetails_pattern = regex("(?<b>(buy|sell))\\s*(?<q>\\d{1,5})\\s*(?<c>[a-z]{3}+)\\s*(at|@)\\s*(?<p>\\d{1,5})p?"); 
	const regex tradeback_pattern = regex("b(ack)*"); 
	const regex stockcode_pattern = regex("(?<c>[a-z]{3}+)"); 
};

template<class T> T RsStocks::readValues(const string& intro_string, const regex& cp, const regex& bp, std::function<pair<bool, T>(const smatch&)>fc, std::function<T ()>fb) const {
        smatch mc;
        smatch mb;
	string input;
	bool ok = true;
	do {
		os << intro_string << endl;
		print_input_prompt();
		getline(is, input);
		to_lower(input);
                if ((regex_match(input, mc, cp) && (mc.size() > 0))) {
			pair<bool, const T&> mv = fc(mc);
         		if (mv.first) {
				return mv.second;
			}
		} else {
			if ((regex_match(input, mb, bp) && (mb.size() > 0))) {
				return fb();
			}
		}
	} while (ok);
}

#define LT(T,PT) [this](PT st, const T & ct)

#define wcvTempCall(FN,CT,CFN,PT) FN<CT>(CFN(), LT(CT,PT)

#define ltCodePrice wcvTempCall(wcvFn,CodePrice,read_stock_price,wcvPt)
#define ltCode wcvTempCall(wcvFn,Code,read_stock_code,wcvPt)
#define ltTradeDetails wcvTempCall(wcvFnM,TradeDetails,read_trade_details,wcvPtM)

#define wcvTemplate(FN,PT) template<class T> void RsStocks::FN(T ct, std::function<fstring(PT, const T&)>af) { \
	PT st = stocks.at(ct.code); \
	if (ct.code != NULL_CODE) { \
		endlsFmt(af(st, ct)); \
	} \
}

wcvTemplate(wcvFn,wcvPt)

wcvTemplate(wcvFnM,wcvPtM)

#endif

