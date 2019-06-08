#include "strategy.h"

class StrategyInterface {
  std::unordered_map<int, Order> *idToOrder,
  std::unordered_map<Ticker, Book> *tickerToBook,
  std::unordered_map<Ticker, Holdings> *tickerToHoldings

  protected:
    StrategyInterface(std::unordered_map<int, Order> *idToOrder,
      std::unordered_map<Ticker, Book> *tickerToBook,
      std::unordered_map<Ticker, Holdings> *tickerToHoldings): idToOrder{idToOrder}, 
      tickerToBook{ticketToBook}, tickerToHoldings{tickerToHoldings} {}

  public:
    Action Strategy::run(
      std::unordered_map<int, Order>,
      std::unordered_map<Ticker, Book>,
      std::unordered_map<Ticker, Holdings>);
};