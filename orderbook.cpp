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
    if (qty <= 0) {
    }
    else{

        if (side == Side::Buy) {
            auto res  = bids.try_emplace(price);
            level& lvl = res.first->second;
            lvl.order_.push_back(order{id,qty});
            auto pos = std::prev(lvl.order_.end());
            id_order[id] = indicator{side,price,pos,res.first,{}};
            resting_count_ += 1;
            lvl.qty_ += qty;

        }
        else {
            auto res  = asks.try_emplace(price);
            level& lvl = res.first->second;
            lvl.order_.push_back(order{id,qty});
            auto pos = std::prev(lvl.order_.end());
            id_order[id] = indicator{side,price,pos,{},res.first};
            resting_count_ += 1;
            lvl.qty_ += qty;
        }
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
    if (it == id_order.end()) {
        return false;
    }
    Side side = it->second.side ;
    auto pos = it->second.pos;
    auto r = it->second.bid_level_;
    auto a = it->second.ask_level_;
    if (side == Side::Buy) {
        level& lvl = it->second.bid_level_->second;
        lvl.qty_ -= pos->qty;
        resting_count_  -=1;
        lvl.order_.erase(pos);
        id_order.erase(it);
        if (lvl.order_.empty()) {
            bids.erase(r);
            return true ;
        }
        return true;
            }

    else {
        level& lvl = it->second.ask_level_->second;;
        lvl.qty_ -= pos->qty;
        resting_count_  -=1;
        lvl.order_.erase(pos);
        id_order.erase(it);
        if (lvl.order_.empty()) {
            asks.erase(a);
            return true ;
        }
        return true;
        }

    }


