#include "adr.h"
#include "strategy_interface.h"
#include "items.h"

#include <unordered_map>
#include <vector>
#include <string>
#include <limits.h>

ADR::ADR(
    std::unordered_map<int, Order> *idToOrder,
    std::unordered_map<Ticker, Book> *tickerToBook,
    std::unordered_map<Ticker, Holdings> *tickerToHoldings,
    std::unordered_map<Ticker, std::pair<Order, Order>> *tickerToOrders): 
    StrategyInterface{idToOrder, tickerToBook, tickerToHoldings, tickerToOrders} {}

const Ticker adr = Ticker::VALE;
const Ticker stock = Ticker::VALBZ;

const int ORDER_QUANTITY = 80;
const int BUY_PRICE = 999;
const int SELL_PRICE = 1001;

const int CONV_COST = 10;

std::vector<Action> ADR::run() {
  auto maxBuyAdr = max((*tickerToBook)[adr].buyOrders);
  auto minSellStock = min((*tickerToBook)[stock].sellOrders);

  int dif = minSellStock.second - maxBuyAdr.second;
  int minQ = maxBuyAdr.first < minSellStock.first ? maxBuyAdr.first : minSellStock.second;

  if (dif * minQ > CONV_COST) {
    return std::vector<Action>{Action{ActionType::BUY, maxBuyAdr.second, adr, maxBuyAdr.first}, 
      Action{ActionType::SELL, minSellStock.second, stock, minSellStock.first}};
  }

  auto maxBuyStock = max((*tickerToBook)[stock].buyOrders);
  auto minSellAdr = min((*tickerToBook)[adr].sellOrders);

  dif = minSellAdr.second - maxBuyStock.second;
  minQ = maxBuyStock.first < minSellAdr.first ? maxBuyStock.first : minSellAdr.first;

  if (dif * minQ > CONV_COST) {
    return std::vector<Action>{Action{ActionType::BUY, maxBuyStock.first, adr, maxBuyStock.second}, 
      Action{ActionType::SELL, minSellAdr.first, stock, minSellAdr.second}};
  }

  return std::vector<Action>{};
}

std::pair<int, int> ADR::min(std::vector<std::pair<int, int>> v) {
  int min = INT_MAX;
  int minQ = 0;

  for (std::pair<int, int> range : v) {
    if (range.second < min) {
      min = range.second;
      minQ = range.first;
    }
  }

  return std::pair<int, int>{minQ, min};
}

std::pair<int, int> ADR::max(std::vector<std::pair<int, int>> v) {
  int max = 0;
  int q = 0;

  for (std::pair<int, int> range : v) {
    if (range.second > max) {
      max = range.second;
      q = range.first;
    }
  }

  return std::pair<int, int>{q, max};
}
