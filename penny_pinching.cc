#include "penny_pinching.h"
#include "strategy_interface.h"
#include "items.h"

#include <unordered_map>
#include <vector>
#include <string>

PennyPinching::PennyPinching(
    std::unordered_map<int, Order> *idToOrder,
    std::unordered_map<Ticker, Book> *tickerToBook,
    std::unordered_map<Ticker, Holdings> *tickerToHoldings,
    std::unordered_map<Ticker, std::pair<Order, Order>> *tickerToOrders): 
    StrategyInterface{idToOrder, tickerToBook, tickerToHoldings, tickerToOrders} {}

const Ticker ticker = Ticker::BOND;

const int ORDER_QUANTITY = 50;
const int BUY_PRICE = 999;
const int SELL_PRICE = 1001;

Action PennyPinching::run() {
  std::pair<Order, Order> &orders = (*tickerToOrders)[ticker];

  int firstDif = ORDER_QUANTITY - orders.first.amount;
  if (firstDif > 0) {
    return Action{ActionType::BUY, firstDif, ticker, BUY_PRICE};
  }

  int secondDif = ORDER_QUANTITY - orders.second.amount;
  if (secondDif > 0) {
    return Action{ActionType::SELL, secondDif, ticker, SELL_PRICE};
  }
}