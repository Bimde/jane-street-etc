#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <vector>
#include <string>
#include <unordered_map>

#include "items.h"

class Portfolio {
	std::unordered_map<int, Order> idToOrder;
	std::unordered_map<Ticker, Book> tickerToBook;
	std::unordered_map<Ticker, Holdings> tickerToHoldings;
	std::unordered_map<Ticker, int> tickerToLastTradedPrice;
	Connection server;

	int cash;

	void updateMaps();
	
  public:
	Portfolio(Connection);
	void run();
};

#endif