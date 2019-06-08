#include <vector>

#include "strategy.h"
#include "items.h"
#include "penny_pinching.h"

Strategy::Strategy(std::unordered_map<int, Order> *idToOrder,
			std::unordered_map<Ticker, Book> *tickerToBook,
			std::unordered_map<Ticker, Holdings> *tickerToHoldings,
      std::unordered_map<Ticker, std::pair<Order, Order>> *tickerToOrders): 
        idToOrder{idToOrder}, tickerToBook{tickerToBook}, tickerToHoldings{tickerToHoldings}, tickerToOrders{tickerToOrders} {
  strategies[StrategyType::PENNY_PINCHING] = new PennyPinching(idToOrder, tickerToBook, tickerToHoldings, tickerToOrders);
}

std::vector<Action> Strategy::runStrategy(std::vector<StrategyType> types) {
  std::vector<Action> output;
  for (auto t : types) {
    auto action = strategies[t]->run();
    if (action.actionType != ActionType::NO_ACTION) {
      output.push_back(action);
    }
  }
}