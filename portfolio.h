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
    std::unordered_map<Ticker, std::pair<Order, Order>> tickerToOrders;
	Connection server;
	Strategy strat;

	int cash;
	
  public:
	Portfolio(Connection);
	void run();
};

#endif