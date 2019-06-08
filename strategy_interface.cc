#include "strategy_interface.h"

StrategyInterface(
	std::unordered_map<int, Order> *idToOrder,
      std::unordered_map<Ticker, Book> *tickerToBook,
      std::unordered_map<Ticker, Holdings> *tickerToHoldings) : 
      idToOrder{idToOrder}, tickerToBook{ticketToBook}, 
      tickerToHoldings{tickerToHoldings} {}