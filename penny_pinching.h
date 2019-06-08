#ifndef PENNY_PINCHING_H
#define PENNY_PINCHING_H

#include "strategy_interface.h"

class PennyPinching : public StrategyInterface {
  public:
    PennyPinching(
      std::unordered_map<int, Order> *,
      std::unordered_map<Ticker, Book> *,
      std::unordered_map<Ticker, Holdings> *,
      std::unordered_map<Ticker, std::pair<Order, Order>> *);
    virtual std::vector<Action> run();
};

#endif