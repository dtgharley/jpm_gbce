#include <ctime>
#include "enums.h"

class TradeDetails {
public:
	TradeDetails() {code = -1; timeStamp = (time_t)-1; quantity = 0; buySell = Buy; price = -1;};
	TradeDetails(int cd, time_t ts, int qy, Bysl bs, int pr) : code(cd), timeStamp(ts), quantity(qy), buySell(bs), price(pr) {};
	
	int code;
	time_t timeStamp;
        int quantity;
	Bysl buySell;
        int price;
};

