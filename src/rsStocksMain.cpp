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

int main(int argc, char *argv[]) {
	RsStocks rsStocks;
	rsStocks.loop();  
}

