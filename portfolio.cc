#include <string>
#include "portfolio.h"
#include "rapidjson/document.h"
#include "items.h"
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

Portfolio::Portfolio(Connection server) : server{server}, pnl{0} {}

void Portfolio::run() {
    while (true) {
        string marketInput = server.read_from_exchange();
        if (marketInput.find("book") != std::string::npos) {
            continue;
        }

        if (marketInput.find("trade") != std::string::npos) {
            continue;
        }

        if (marketInput.find("ack") != std::string::npos) {
            continue;
        }

        if (marketInput.find("out") != std::string::npos) {
            continue;
        }

        if (marketInput.find("fill") != std::string::npos) {
            continue;
        }

        if (marketInput.find("reject") != std::string::npos) {
            continue;
        }

        if (marketInput.find("open") != std::string::npos) {
            continue;
        }

        if (marketInput.find("close") != std::string::npos) {
            continue;
        }

        if (marketInput.find("hello") != std::string::npos) {
            continue;
        }

        if (marketInput.find("error") != std::string::npos) {
            continue;
        }
    }
}