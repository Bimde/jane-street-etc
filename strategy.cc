#include <vector>

#include "strategy.h"
#include "items.h"
#include "penny_pinching.h"
#include "adr.h"

Strategy::~Strategy() {
  delete strategies[StrategyType::PENNY_PINCHING];
  delete strategies[StrategyType::ADR_ARBITRAGE];
}

Strategy::Strategy(std::unordered_map<int, Order> *idToOrder,
			std::unordered_map<Ticker, Book> *tickerToBook,
			std::unordered_map<Ticker, Holdings> *tickerToHoldings,
      std::unordered_map<Ticker, std::pair<Order, Order>> *tickerToOrders): 
        idToOrder{idToOrder}, tickerToBook{tickerToBook}, tickerToHoldings{tickerToHoldings}, tickerToOrders{tickerToOrders} {
  strategies[StrategyType::PENNY_PINCHING] = new PennyPinching(idToOrder, tickerToBook, tickerToHoldings, tickerToOrders);
  strategies[StrategyType::ADR_ARBITRAGE] = new ADR(idToOrder, tickerToBook, tickerToHoldings, tickerToOrders);
}

std::vector<Action> Strategy::runStrategy(std::vector<StrategyType> types) {
  std::vector<Action> output;
  for (auto t : types) {
    auto actions = strategies[t]->run();
    for (Action a : actions) {
      if (a.actionType != ActionType::NO_ACTION) {
        output.push_back(a);
      }
    }
  }

  return output;
}