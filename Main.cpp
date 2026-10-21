//
// Created by Ulysse B on 16/10/2026.
//

#include <iostream>
#include "orderbook.h"
#include<optional>

int main() {
    orderbook b;

    add_limit(1023,Side::Buy,105,12);
    add_limit(1021,Side::Buy,106,12);
    add_limit(1023,Side::Buy,107,12);
    add_limit(1023,Side::Sell,109,12);

    std::optional<std::int64_t> a = b.best_bid();
    std::optional<std::int64_t> c = b.best_ask();
}