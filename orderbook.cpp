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
    if (side == Side::Buy) {
        bids[price].push_back(order{id,qty});
    }
    else {
        asks[price].push_back(order{id,qty});
    }
}
