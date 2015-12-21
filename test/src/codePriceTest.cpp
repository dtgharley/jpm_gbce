//! codePriceTest.cpp

#include "codePrice.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(codePrice)

BOOST_AUTO_TEST_CASE(CodePriceNullaryConstructor)
{
	CodePrice c;	
	BOOST_CHECK(c.code == -1);
	BOOST_CHECK(c.price == -1);
}

BOOST_AUTO_TEST_CASE(CodePriceTypicalConstructor_01)
{
	CodePrice c(2, 100);	
	BOOST_CHECK(c.code == 2);
	BOOST_CHECK(c.price == 100);
}

BOOST_AUTO_TEST_SUITE_END()

