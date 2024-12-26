//
// Created by Miraitowa_zcx on 24-12-23.
//

#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
#include <unordered_map>
#include <vector>

#include "Product.hpp"

namespace pos_system {
    class Inventory {
    public:
        Inventory();
        bool saveProduct(int id);
        bool loadProduct();
        int addProduct(const Product& product, int quantity);
        int updateProduct(int productId, const Product& product, int quantity);
        int deleteProduct(int productId);
        std::optional<Product> selectProduct(int productId) const;
        int getProductId(const std::string& productName) const;
        std::vector<int> getProductType(const std::string& productType);
        int getProductQuantity(int productId) const;
        int printInventory() const;

    private:
        std::unordered_map<int, std::pair<Product, int>> products;
        std::unordered_map<std::string, int> nameToIdMap;
        std::unordered_map<std::string, int> typeToIdMap;
        int currentId;
    };
} // namespace pos_system

#endif // INVENTORY_HPP
