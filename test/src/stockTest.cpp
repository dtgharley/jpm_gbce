//! stockTest.cpp

#include "stock.h"
#include <boost/test/unit_test.hpp>

using namespace std;
using namespace boost;

BOOST_AUTO_TEST_SUITE(stock)

BOOST_AUTO_TEST_CASE(stockTypicalConstructor_01)
{
	Stock s("TEA", Common, 0, -1, 100);	
	BOOST_CHECK(s.code == "TEA");
	BOOST_CHECK(s.cop == Common);
	BOOST_CHECK(s.lastDividend == 0);
	BOOST_CHECK(s.fixedDividend == -1);
	BOOST_CHECK(s.parValue == 100);
}

BOOST_AUTO_TEST_CASE(stockTypicalTrades_01)
{
	Stock s("GIN", Preferred, 8, 2, 100);	
	BOOST_CHECK(s.code == "GIN");
	BOOST_CHECK(s.cop == Preferred);
	BOOST_CHECK(s.lastDividend == 8);
	BOOST_CHECK(s.fixedDividend == 2);
	BOOST_CHECK(s.parValue == 100);
	BOOST_CHECK(s.trades.size() == (size_t)0);
	time_t c1 = time(0);
	TradeDetails t1(1, c1, 100, Sell, 99);
	s.trades.push_back(t1);
	BOOST_CHECK(s.trades.at(0).code == 1);
	BOOST_CHECK(s.trades.at(0).timeStamp == c1);
	BOOST_CHECK(s.trades.at(0).quantity == 100);
	BOOST_CHECK(s.trades.at(0).buySell == Sell);
	BOOST_CHECK(s.trades.at(0).price == 99);
	BOOST_CHECK(s.trades.size() == (size_t)1);
	time_t c2 = time(0);
	TradeDetails t2(2, c2, 150, Buy, 200);	
	s.trades.push_back(t2);
	BOOST_CHECK(s.trades.size() == (size_t)2);
	BOOST_CHECK(s.trades.at(1).code == 2);
	BOOST_CHECK(s.trades.at(1).timeStamp == c2);
	BOOST_CHECK(s.trades.at(1).quantity == 150);
	BOOST_CHECK(s.trades.at(1).buySell == Buy);
	BOOST_CHECK(s.trades.at(1).price == 200);
	BOOST_CHECK(s.trades.size() == (size_t)2);
        
}

BOOST_AUTO_TEST_SUITE_END()

