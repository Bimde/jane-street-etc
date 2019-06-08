#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <vector>
#include <unordered_map>

#include "items.h"

class Portfolio {
	std::unordered_map<int, Order> idToOrder;
	std::unordered_map<Ticker, Book> tickerToBook;
	std::unordered_map<Ticker, Holdings> tickerToHoldings;
	Connection server;
	
  public:
	Portfolio(Connection);
	void run();
};

#endif