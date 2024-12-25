//
// Created by Miraitowa_zcx on 24-12-23.
//

#ifndef SALE_TRANSACTION_HPP
#define SALE_TRANSACTION_HPP

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

#include "Inventory.hpp"
#include "Product.hpp"

namespace pos_system {
    class SaleTransaction {
    public:
        int saleProduct(const Product& product, int quantity);
        int finalizeSale(Inventory& inventory, int pricePayable);
        int printReceipt();
        int clearSale();

    private:
        std::vector<std::pair<Product, int>> items;
        double total = 0.0;
    };
} // namespace pos_system

#endif // SALE_TRANSACTION_HPP
