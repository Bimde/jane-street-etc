#include <string>
#include <iostream>
#include "portfolio.h"
#include "strategy.h"
#include "rapidjson/document.h"
#include "items.h"
#include "connection.h"

#include <map>

using std::string;
using std::to_string;
using namespace rapidjson;

Book stringToBook(string json) {
    Book book;

    const char *cstar = json.c_str();
    Document d;
    d.Parse(cstar);

    assert(d.IsObject());
    assert(d.HasMember("type"));
    assert(d.HasMember("symbol"));
    assert(d.HasMember("buy"));
    assert(d.HasMember("sell"));

    const Value&buyData = d["buy"];
    for (SizeType i = 0; i < buyData.Size(); i++) {
        const Value&b = buyData[i];
        assert(b[0].IsInt());
        assert(b[1].IsInt());
        std::pair<int,int> pair = std::make_pair(b[0].GetInt(), b[1].GetInt());
        book.buyOrders.emplace_back(pair);
    }

    const Value&sellData = d["sell"];
    for (SizeType i = 0; i < sellData.Size(); i++) {
        const Value&b = sellData[i];
        assert(b[0].IsInt());
        assert(b[1].IsInt());
        std::pair<int,int> pair = std::make_pair(b[0].GetInt(), b[1].GetInt());
        book.sellOrders.emplace_back(pair);
    }

    return book;
}

int stringToTrade(string json) {
    int price;
    int quantity;
    const char *cstar = json.c_str();
    Document d;
    d.Parse(cstar);

    assert(d.HasMember("price"));
    assert(d.HasMember("size"));

    price = d["price"].GetInt();
    quantity = d["size"].GetInt();

    return price;
}

int stringToAck(string json) {
    const char *cstar = json.c_str();
    Document d;
    d.Parse(cstar);
    assert(d.HasMember("order_id"));
    return d["order_id"].GetInt();
}

Error stringToReject(string json) {
    const char *cstar = json.c_str();
    Document d;
    d.Parse(cstar);
    assert(d.HasMember("order_id"));
    assert(d.HasMember("error"));
    Error e;
    e.orderId = d["order_id"].GetInt();
    e.error = d["error"].GetString();
    return e;
}

Fill stringToFill(string json) {
    const char *cstar = json.c_str();
    Document d;
    d.Parse(cstar);
    assert(d.HasMember("order_id"));
    assert(d.HasMember("symbol"));
    assert(d.HasMember("dir"));
    assert(d.HasMember("price"));
    assert(d.HasMember("size"));
    Fill f;
    f.orderId = d["order_id"].GetInt();
    f.symbol = d["symbol"].GetString();
    f.dir = d["dir"].GetString();
    f.price = d["price"].GetInt();
    f.size = d["size"].GetInt();
    return f;
}

string stringToError(string json) {
    const char *cstar = json.c_str();
    Document d;
    d.Parse(cstar);
    return d["error"].GetString();
}

int stringToOut(string json) {
    const char *cstar = json.c_str();
    Document d;
    d.Parse(cstar);
    assert(d.HasMember("order_id"));
    return d["order_id"].GetInt();
}

string getStringForKey(string json, string key) {
    const char *cstar = json.c_str();
    Document d;
    d.Parse(cstar);
    assert(d.HasMember(key.c_str()));
    return d[key.c_str()].GetString();
}


std::map<std::string, Ticker> stringToTickerEnum = {
                                                        {"BOND", Ticker::BOND},
                                                        {"VALBZ", Ticker::VALBZ},
                                                        {"VALE", Ticker::VALE},
                                                        {"GS", Ticker::GS},
                                                        {"MS", Ticker::MS},
                                                        {"WFC", Ticker::WFC},
                                                        {"XLF", Ticker::XLF}
                                                    };

Portfolio::Portfolio(Connection server) : server{server}, cash{0}, strat{Strategy{&idToOrder, &tickerToBook, &tickerToHoldings, &tickerToOrders}} {}

const std::vector<StrategyType> strats = {StrategyType::PENNY_PINCHING};

void Portfolio::run() {
    while (true) {
        string marketInput = server.read_from_exchange();
        if (marketInput.find("book") != std::string::npos) {
            string symbol = getStringForKey(marketInput, "symbol");
            Book b = stringToBook(marketInput);
            tickerToBook[stringToTickerEnum[symbol]] = b;
            continue;
        }

        if (marketInput.find("trade") != std::string::npos) {
            // Get trade object
            continue;
        }

        if (marketInput.find("ack") != std::string::npos) {
            int stockId = stringToAck(marketInput);
            idToOrder[stockId].isAcked = true;
            continue;
        }

        if (marketInput.find("out") != std::string::npos) {
            int orderId = stringToOut(marketInput);
            idToOrder.erase(orderId);
            continue;
        }

        if (marketInput.find("fill") != std::string::npos) {
            Fill fillItem = stringToFill(marketInput);
            Ticker symb = stringToTickerEnum[fillItem.symbol];
            if (tickerToHoldings.find(symb) == tickerToHoldings.end()) {
                tickerToHoldings[symb] = Holdings{symb, 0};
            }

            Holdings &h = tickerToHoldings[symb];
                
            if (fillItem.dir == "BUY") {
                h.amount += fillItem.size;
                tickerToOrders[symb].first.amount -= fillItem.size;
                if (tickerToOrders[symb].first.amount < 0) {
                    std::cout << "tickerToOrders is negative BUY!" << std::endl;
                }
            } else if (fillItem.dir == "SELL") {
                h.amount -= fillItem.size;
                tickerToOrders[symb].second.amount -= fillItem.size;
                if (tickerToOrders[symb].second.amount < 0) {
                    std::cout << "tickerToOrders is negative SELL!" << std::endl;
                }
            } else {
                std::cout << "FILL command was not BUY or SELL, it was " << fillItem.dir << std::endl; 
            }
            continue;
        }

        if (marketInput.find("reject") != std::string::npos) {
            Error err = stringToReject(marketInput);
            std::cout << "!!!!!!!!! " << err.orderId << " " << err.error << std::endl;
            continue;
        }

        if (marketInput.find("open") != std::string::npos) {
            continue;
        }

        if (marketInput.find("close") != std::string::npos) {
            std::cout << "Close: " << marketInput << std::endl;
            // TODO: Write for close!!!!
            return;
        }

        if (marketInput.find("hello") != std::string::npos) {
            continue;
        }

        if (marketInput.find("error") != std::string::npos) {
            std::cout << stringToError(marketInput) << std::endl;
            continue;
        }
        
        std::vector<Action> action = strat.runStrategy(strats);
    }

}