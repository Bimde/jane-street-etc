#include "strategy.h"
#include <vector>
#include "items.h"
#include "portfolio.h"

Strategy::Strategy(std::unordered_map<int, Order> *idToOrder,
			std::unordered_map<Ticker, Book> *tickerToBook,
			std::unordered_map<Ticker, Holdings> *tickerToHoldings): 
        idToOrder{idToOrder}, tickerToBook{tickerToBook}, tickerToHoldings{tickerToHoldings} {
          
        }

std::vector<Action> Strategy::runStrategy(std::vector<StrategyType> types) {
  std::vector<Action> output;
  for (auto t : types) {
    auto action = strategies[t].run();
    if (action.actionType != ActionType::NO_ACTION) {
      output.push_back(action);
    }
  }
}