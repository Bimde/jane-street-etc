#ifndef STRATEGY_H
#define STRATEGY_H

#include <unordered_map>
#include <vector>
#include "items.h"
#include "strategy_interface.h"

enum StrategyType {
	BASIC
};

class Strategy {
  public:
		Strategy(
			std::unordered_map<int, Order> *,
			std::unordered_map<Ticker, Book> *,
			std::unordered_map<Ticker, Holdings> *);
		std::vector<Action> runStrategy(std::vector<StrategyType>);
	private:
		std::unordered_map<StrategyType, StrategyInterface> strategies;
		std::unordered_map<int, Order> *idToOrder;
		std::unordered_map<Ticker, Book> *tickerToBook;
		std::unordered_map<Ticker, Holdings> *tickerToHoldings;
};

#endif