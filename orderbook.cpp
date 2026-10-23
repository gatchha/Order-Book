//
// Created by Ulysse B on 16/10/2026.
//

#include <optional>
#include <functional>
#include "orderbook.h"

std::optional<std::int64_t> orderbook::best_bid() const {
    if (bids.empty()) {
        return std::nullopt;
    }
    return bids.begin()->first;

}

std::optional<std::int64_t> orderbook::best_ask() const {
    if (asks.empty()) {
        return std::nullopt;
    }
    return asks.begin()->first;
}


void orderbook::add_limit(std::uint64_t id, Side side,std::int64_t price, std::int64_t qty) {
    id_order_[id] = indicator{side,price};
    if (side == Side::Buy) {
        level& lvl = bids[price];
        lvl.order_.push_back(order{id,qty});
        resting_count_ += 1;
        lvl.qty_ += qty;

    }
    else {
        level& lvl = asks[price];
        lvl.order_.push_back(order{id,qty});
        resting_count_ += 1;
        lvl.qty_ += qty;
    }
}

std::int64_t orderbook::volume_at(Side side, std::int64_t price) const{
    if (side == Side::Buy) {
        auto it = bids.find(price);
        if (it == bids.end()) {
            return 0;
        }
        else {
            return it->second.qty_;
        }
    }
    else {
        auto it = asks.find(price);
        if (it == asks.end()) {
            return 0;
        }
        else {
            return it->second.qty_;
        }
    }
}

std::size_t orderbook::count_order()const{
   return resting_count_;
}

bool orderbook::cancel_order(std::uint64_t id) {
    auto it = id_order.find(id);
    if (it != id_order.end()){
        std::int64_t price = it->second.price;
        if (it->second.side == Side::Buy) {
        bids[price].order_.erase(id);
        }
    }
    else {
        return false;
    }



}