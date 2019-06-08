#ifndef STRATEGY_INTERFACE_H
#define STRATEGY_INTERFACE_H

#include <unordered_map>

#include "strategy.h"

class StrategyInterface {
  std::unordered_map<int, Order> *idToOrder,
  std::unordered_map<Ticker, Book> *tickerToBook,
  std::unordered_map<Ticker, Holdings> *tickerToHoldings

  protected:
    StrategyInterface(
      std::unordered_map<int, Order> *idToOrder,
      std::unordered_map<Ticker, Book> *tickerToBook,
      std::unordered_map<Ticker, Holdings> *tickerToHoldings);

  public:
    Action Strategy::run() = 0;
};

#endif