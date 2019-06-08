#ifndef PENNY_PINCHING_H
#define PENNY_PINCHING_H

#include "strategy_interface.h"

class PennyPinching : public StrategyInterface {
  public:
    PennyPinching(
      std::unordered_map<int, Order> *idToOrder,
      std::unordered_map<Ticker, Book> *tickerToBook,
      std::unordered_map<Ticker, Holdings> *tickerToHoldings,
      std::unordered_map<Ticker, std::pair<Order, Order>> *);
    virtual Action run();
};

#endif