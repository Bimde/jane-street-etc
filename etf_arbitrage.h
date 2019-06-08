#ifndef ETF_ARBITRAGE_H
#define ETF_ARBITRAGE_H

#include "strategy_interface.h"

class ETFArbitrage : public StrategyInterface {
  public:
    ETFArbitrage(
      std::unordered_map<int, Order> *,
      std::unordered_map<Ticker, Book> *,
      std::unordered_map<Ticker, Holdings> *,
      std::unordered_map<Ticker, std::pair<Order, Order>> *);
    virtual std::vector<Action> run() override;
  private:
    std::pair<int, int> min(std::vector<std::pair<int, int>>);
    std::pair<int, int> max(std::vector<std::pair<int, int>>);
};

#endif