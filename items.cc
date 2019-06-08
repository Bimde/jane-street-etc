#include <vector>

#include <utility>

#include "items.h"

Book& Book::operator=(const Book& b) {
	buyOrders = b.buyOrders;
	sellOrders = b.sellOrders;
}

Book& Book::operator=(Book&& b) {
	std::swap(buyOrders, b.buyOrders);
	std::swap(sellOrders, b.sellOrders);
}