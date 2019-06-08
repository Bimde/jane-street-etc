#include <vector>
#include <utility>

#include "items.h"

Book::Book() {}

Book::Book(std::vector<std::pair<int, int>>& buy, 
		   std::vector<std::pair<int, int>>& sell) {
	std::swap(buyOrders, buy);
	std::swap(sellOrders, sell);
}

Book::Book(const Book& b) {
	buyOrders = b.buyOrders;
	sellOrders = b.sellOrders;
}

Book::Book(Book&& b) {
	std::swap(buyOrders, b.buyOrders);
	std::swap(sellOrders, b.sellOrders);
}

Book& Book::operator=(const Book& b) {
	buyOrders = b.buyOrders;
	sellOrders = b.sellOrders;
}

Book& Book::operator=(Book&& b) {
	std::swap(buyOrders, b.buyOrders);
	std::swap(sellOrders, b.sellOrders);
}