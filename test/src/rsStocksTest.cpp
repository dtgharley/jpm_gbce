//! rsStocksTest.cpp

#include "rsST.h"
#include <boost/test/unit_test.hpp>

#ifdef TEST_TIMEOUT
namespace utf = boost::unit_test;
#endif 

BOOST_FIXTURE_TEST_SUITE(rsStocks, RsST)

BOOST_AUTO_TEST_CASE(RsStocksNullaryConstructor)
{
	BOOST_CHECK(stocks.size() > 0);
	BOOST_CHECK(codeMap.size() > 0);
	BOOST_CHECK(codeMap.size() == stocks.size());
}

#ifdef TEST_TIMEOUT
BOOST_AUTO_TEST_CASE(RsStocksTypicalReadStockPrice_01, *utf::timeout(2))
#else
BOOST_AUTO_TEST_CASE(RsStocksTypicalReadStockPrice_01)
#endif
{
	read_stock_price("GIN 99p");
	BC_CP(code,3);
	BC_CP(price,99);
	read_stock_price("TEA  01");
	BC_CP(code,0);
	BC_CP(price,1);
	read_stock_price("pop  202");
	BC_CP(code,1);
	BC_CP(price,202);
	i << "rum 202" << endl;
	i << "back" << endl;
	read_stock_price();
	BC_CP(code,NULL_CODE);
	BC_CP(price,NULL_PRICE);
}

#ifdef TEST_TIMEOUT
BOOST_AUTO_TEST_CASE(RsStocksTypicalReadTradeDetails_01, *utf::timeout(2))
#else
BOOST_AUTO_TEST_CASE(RsStocksTypicalReadTradeDetails_01)
#endif
{
	read_trade_details("Buy 200 GIN @ 99p");
	BC_TD(code,3);
	BC_TD_TR;
	BC_TD(quantity,200);
	BC_TD(buySell,Buy);
	BC_TD(price,99);
	read_trade_details("buy 20 TEA at 88");
	BC_TD(code,0);
	BC_TD_TR;
	BC_TD(quantity,20);
	BC_TD(buySell,Buy);
	BC_TD(price,88);
	read_trade_details("sell 202 pop at 50p");
	BC_TD(code,1);
	BC_TD_TR;
	BC_TD(quantity,202);
	BC_TD(buySell,Sell);
	BC_TD(price,50);
	i << "sell99 rum at 50p" << endl;
	i << "b" << endl;
	read_trade_details();
	BC_TD(code,NULL_CODE);
	BC_TD(timeStamp,NULL_TIME);
	BC_TD(quantity,NULL_QUANTITY);
	BC_TD(buySell,NULL_BYSL);
	BC_TD(price,NULL_PRICE);
}

#ifdef TEST_TIMEOUT
BOOST_AUTO_TEST_CASE(RsStocksTypicalReadStockCode_01, *utf::timeout(2))
#else
BOOST_AUTO_TEST_CASE(RsStocksTypicalReadStockCode_01)
#endif
{
	read_stock_code("GIN");
	BC_SC(3);
	read_stock_code("TEA");
	BC_SC(0);
	read_stock_code("pop");
	BC_SC(1);
	i << "sell99 rum at 50p" << endl;
	i << "b" << endl;
	read_stock_code();
	BC_SC(NULL_CODE);
}

#ifdef TEST_TIMEOUT
BOOST_AUTO_TEST_CASE(RsStocksTypicalCalculateVwi_01, *utf::timeout(2))
#else
BOOST_AUTO_TEST_CASE(RsStocksTypicalCalculateVwi_01)
#endif
{
	push_trade_details("Buy 200 GIN @ 99p");
	push_trade_details("Buy 200 GIN @ 99p");
	calc_vwi(stocks.at(td.code));
	BC_VWI(99);
	push_trade_details("Buy 100 TEA @ 22p");
	push_trade_details("Buy 2002 TEA @ 5p");
	push_trade_details("Sell 1 TEA @ 5000p");
	calc_vwi(stocks.at(td.code));
	BC_VWI(8);
}

#ifdef TEST_TIMEOUT
BOOST_AUTO_TEST_CASE(RsStocksTypicalLoopAction_01, *utf::timeout(2))
#else
BOOST_AUTO_TEST_CASE(RsStocksTypicalLoopAction_01)
#endif
{
	i << "d" << endl;
	i << "gin 22p" << endl;
	loop();
	BC_OC("The Dividend Yield for GIN at 22p is 9%");
	i << "p" << endl;
	i << "pop 45" << endl;
	loop();
	BC_OC("The Price to Earnings Ratio for POP at 45p is 5.62");
	i << "r" << endl;
	i << "sell 200 gin at 50p" << endl;
	loop();
	BC_OT("Trade recorded for sale of 200 GIN shares at 50p on ",3);
	i << "v" << endl;
	i << "gin" << endl;
	loop();
	BC_OC("The Volume Weighted Stock Price for GIN is 50p");
	i << "g" << endl;
	loop();
	BC_OC("The GBCE All Share Index is currently 50p");
}

BOOST_AUTO_TEST_SUITE_END()

