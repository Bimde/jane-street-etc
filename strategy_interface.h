#ifndef STRATEGY_INTERFACE_H
#define STRATEGY_INTERFACE_H

#include <unordered_map>

#include "items.h"

class StrategyInterface {

  protected:
    StrategyInterface(
      std::unordered_map<int, Order> *,
      std::unordered_map<Ticker, Book> *,
      std::unordered_map<Ticker, Holdings> *,
      std::unordered_map<Ticker, std::pair<Order, Order>> *);
    std::unordered_map<int, Order> *idToOrder;
    std::unordered_map<Ticker, Book> *tickerToBook;
    std::unordered_map<Ticker, Holdings> *tickerToHoldings;
    std::unordered_map<Ticker, std::pair<Order, Order>> *tickerToOrders;
    
  public:
    virtual Action run() = 0;
};

#endif