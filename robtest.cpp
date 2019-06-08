
/* HOW TO RUN
   1) Configure things in the Configuration class
   2) Compile: g++ -o bot.exe bot.cpp
   3) Run in loop: while true; do ./bot.exe; sleep 1; done
*/

/* C includes for networking things */
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

/* C++ includes */
#include <string>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <sstream>
#include "items.h"
#include "rapidjson/document.h"
/* The Configuration class is used to tell the bot how to connect
   to the appropriate exchange. The `test_exchange_index` variable
   only changes the Configuration when `test_mode` is set to `true`.
*/

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

string getStringForKey(string json, string key) {
    const char *cstar = json.c_str();
    Document d;
    d.Parse(cstar);
    assert(d.HasMember(key.c_str()));
    return d[key.c_str()].GetString();
}

Hello stringToHello(string json) {
    Hello h;

    const char *cstar = json.c_str();
    Document d;
    d.Parse(cstar);
    const Value& symbs = d["symbols"];

    assert(symbs.IsArray());
    for (SizeType i = 0; i < symbs.Size(); i++) {
        const Value& data = symbs[i];
        string s = data["symbol"].GetString();
        int n = data["position"].GetInt();
        
        std::pair<string,int> pair = std::make_pair(s, n);
        h.symbols.emplace_back(pair);
    }
    return h;
}

int main(int argc, char *argv[]) {
    std::string json = R"({"type":"book","symbol":"VALBZ","buy":[[4201,9]],"sell":[[4202,5],[4203,18]]})";
    std::string jsonTrade = R"({"type":"trade","symbol":"SYM","price":101,"size":21})";
    std::string jsonAck = R"({"type":"ack","order_id":69420})";
    std::string jsonError = R"({"type":"reject","order_id":69420,"error":"Wow an error1"})";
    std::string jsonFill = R"({"type":"fill","order_id":100,"symbol":"SYML","dir":"BUY","price":69,"size":1})";
    std::string jsonOut = R"({"type":"out","order_id":69420})";
    std::string jsonHello = R"({"type":"hello","symbols":[{"symbol":"SYM","position":12}, {"symbol":"SYM1","position":13}, {"symbol":"SYM2","position":14}]})";
    Book b = stringToBook(json);  
    std::cout << "Buys" << std::endl;
    for (auto im : b.buyOrders) {
        std::cout << im.first << ", " << im.second << std::endl;
    }
    std::cout << "Sells" << std::endl;
    for (auto im : b.sellOrders) {
        std::cout << im.first << ", " << im.second << std::endl;
    }
    std::cout << "Kek" << std::endl;
    
    std::cout << stringToTrade(jsonTrade) << std::endl;

    std::cout << "ACK: " << stringToAck(jsonAck) << std::endl;
    
    Error err = stringToReject(jsonError);
    std::cout << "Error: " << err.orderId << " " << err.error << std::endl;
    
    Fill f = stringToFill(jsonFill);
    std::cout << "Fill: " << 
    f.orderId << " " << 
    f.symbol << " " <<
    f.dir << " " <<
    f.price << " " <<
    f.size << " " << std::endl;

    std::cout << "OUT: " << stringToOut(jsonOut) << std::endl;
    
    std::cout << getStringForKey(json, "symbol") << std::endl;

    Hello h = stringToHello(jsonHello);
    for (auto thing : h.symbols) {
        std::cout << thing.first << " " << thing.second << std::endl;
    }

    return 0;
}
