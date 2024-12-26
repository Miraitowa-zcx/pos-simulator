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
        Product(std::string name, double price, std::string type);
        Product(int id, std::string name, double price, std::string type);
        [[nodiscard]] int getId() const;
        [[nodiscard]] std::string getName() const;
        [[nodiscard]] double getPrice() const;
        [[nodiscard]] std::string getType() const;

    private:
        int id;
        std::string name;
        double price;
        std::string type;
    };
} // namespace pos_system

#endif // PRODUCT_HPP
