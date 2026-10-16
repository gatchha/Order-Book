//
// Created by Ulysse B on 15/10/2026.
//

#ifndef ORDER_BOOK_ORDERBOOK_H
#define ORDER_BOOK_ORDERBOOK_H

#include <cstdint>
#include <list>
#include <map>
#include <functional>


struct order {
    std::uint64_t id;
    std::int64_t qty;
};

struct orderbook {
    std::map<std::int64_t,std::list<order>,std::greater<std::int64_t>> bids ;
    std::map<std::int64_t,std::list<order>> ask ;
};
#endif //ORDER_BOOK_ORDERBOOK_H