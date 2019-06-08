#ifndef STRATEGY_H
#define STRATEGY_H

#include <unordered_map>
#include "items.h"

class Strategy {
  public:
	Strategy(Portfolio);
	Action runStrategy(
		std::unordered_map<int, Order> idToOrder,
		std::unordered_map<Ticker, Book> tickerToBook,
		std::unordered_map<Ticker, Holdings> tickerToHoldings);
};

#endif