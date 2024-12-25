//
// Created by Miraitowa_zcx on 24-12-23.
//

#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>

namespace pos_system {
    class Product {
    public:
        Product();
        Product(std::string name, double price);
        Product(int id, std::string name, double price);
        [[nodiscard]] int getId() const;
        [[nodiscard]] std::string getName() const;
        [[nodiscard]] double getPrice() const;

    private:
        int id;
        std::string name;
        double price;
    };
} // namespace pos_system

#endif // PRODUCT_HPP
