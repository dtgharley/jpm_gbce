//! tradeDetailsTest.cpp

#include "tradeDetails.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(tradeDetails)

BOOST_AUTO_TEST_CASE(TradeDetailsNullaryConstructor)
{
	TradeDetails t;	
	BOOST_CHECK(t.code == NULL_CODE);
	BOOST_CHECK(t.timeStamp == NULL_TIME);
	BOOST_CHECK(t.quantity == NULL_QUANTITY);
	BOOST_CHECK(t.buySell == NULL_BYSL);
	BOOST_CHECK(t.price == NULL_PRICE);
}

BOOST_AUTO_TEST_CASE(TradeDetailsTypicalConstructor_01)
{
	time_t c = time(0);
	TradeDetails t(2, c, 100, Sell, 99);	
	BOOST_CHECK(t.code == 2);
	BOOST_CHECK(t.timeStamp == c);
	BOOST_CHECK(t.quantity == 100);
	BOOST_CHECK(t.buySell == Sell);
	BOOST_CHECK(t.price == 99);
}

BOOST_AUTO_TEST_SUITE_END()

