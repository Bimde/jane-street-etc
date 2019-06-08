#include "strategy_interface.h"
#include "items.h"

StrategyInterface::StrategyInterface(
	std::unordered_map<int, Order> *idToOrder,
	std::unordered_map<Ticker, Book> *tickerToBook,
	std::unordered_map<Ticker, Holdings> *tickerToHoldings,
	std::unordered_map<Ticker, std::pair<Order, Order>> *tickerToOrders) : 
		idToOrder{idToOrder}, tickerToBook{tickerToBook}, 
      	tickerToHoldings{tickerToHoldings}, tickerToOrders{tickerToOrders} {}