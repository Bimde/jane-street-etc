#ifndef ITEMS_H
#define ITEMS_H

#include <vector>
#include <pair>

enum Ticker {BOND, VALBZ, VALE, GS, MS, WFC, XLF};

enum ActionType {BUY, SELL, CONVERT_TO, CONVERT_FROM};

struct Action {
	ActionType actionType;
	int amount;
};

struct Order {
	int id;
	Ticker ticker;
	ActionType actionType;
	int amount;
	bool isAcked;
};

struct Book {
	std::vector<std::pair<int, int>> buyOrders;
	std::vector<std::pair<int, int>> sellOrders;
};

struct Holdings {
	Ticker ticker;
	int amount;
};

#endif