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

struct level {
    std::list<order> order_;
    std::int64_t qty_ = 0;
};

struct orderbook {
    private: std::map<std::int64_t,level,std::greater<>> bids ;
    std::map<std::int64_t,level> asks ;
    std::size_t resting_count_ = 0;
    public:[[nodiscard]] std::optional<std::int64_t> best_bid() const;
    [[nodiscard]] std::optional<std::int64_t> best_ask() const;
    void add_limit(std::uint64_t id, Side side,std::int64_t price, std::int64_t qty);
    [[nodiscard]] std::size_t count_order(Side side, std::int64_t price) const;
    std::int64_t volume_at(Side side, std::int64_t price) const ;
};




#endif //ORDER_BOOK_ORDERBOOK_H