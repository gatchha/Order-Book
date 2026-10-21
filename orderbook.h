//
// Created by Ulysse B on 15/10/2026.
//

#ifndef ORDER_BOOK_ORDERBOOK_H
#define ORDER_BOOK_ORDERBOOK_H

#include <cstdint>
#include <list>
#include <map>
#include <functional>
#include<optional>


enum class Side {Buy, Sell};


struct order {
    std::uint64_t id;
    std::int64_t qty;
};

struct orderbook {
    std::map<std::int64_t,std::list<order>,std::greater<std::int64_t>> bids ;
    std::map<std::int64_t,std::list<order>> asks ;
    std::optional<std::int64_t> best_bid() const;

    std::optional<std::int64_t> best_ask() const;
    void add_limit(std::uint64_t id, Side side,std::int64_t price, std::int64_t qty);
};




#endif //ORDER_BOOK_ORDERBOOK_H