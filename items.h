#ifndef ITEMS_H
#define ITEMS_H

#include <vector>

enum Ticker {BOND, VALBZ, VALE, GS, MS, WFC, XLF};

enum ActionType {NO_ACTION, BUY, SELL, CONVERT_TO, CONVERT_FROM};

struct Action {
	ActionType actionType;
	int amount;
	Ticker ticker;
	int price;
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

	Book();
	Book(std::vector<std::pair<int, int>>&, 
		 std::vector<std::pair<int, int>>&);
	Book(const Book&);
	Book(Book&&);

	Book& operator=(const Book& b);
	Book& operator=(Book&& b);
};

struct Holdings {
	Ticker ticker;
	int amount;
};

#endif