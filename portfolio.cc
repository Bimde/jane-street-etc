#include <string>
#include "portfolio.h"
#include "rapidjson/document.h"
#include "items.h"
using namespace rapidjson;

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

int stringToOut(string json) {
    const char *cstar = json.c_str();
    Document d;
    d.Parse(cstar);
    assert(d.HasMember("order_id"));
    return d["order_id"].GetInt();
}