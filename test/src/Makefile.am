bin_PROGRAMS = rsST

rsST_SOURCES = rsStocksMainTest.cpp rsStocksTest.cpp "${top_srcdir}/src/rsStocks.cpp" codePriceTest.cpp tradeDetailsTest.cpp stockTest.cpp

rsST_CPPFLAGS = --std=c++11 "-I${top_srcdir}/include" "-I${top_srcdir}/test/include"

rsST_LDFLAGS = "${top_srcdir}/src/rsS-rsStocks.o" -lboost_regex -lboost_unit_test_framework

