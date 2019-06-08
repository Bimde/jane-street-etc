#ifndef ADR_H
#define ADR_H

#include "strategy_interface.h"

class ADR : public StrategyInterface {
  public:
    ADR(
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