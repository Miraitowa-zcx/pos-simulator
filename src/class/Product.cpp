//
// Created by Miraitowa_zcx on 24-12-23.
//

#include "../include/class/Product.hpp"

namespace pos_system {

    // 无参构造函数
    Product::Product() : id(0), price(0.0) {}

    // 有参构造函数
    Product::Product(std::string name, const double price, std::string type)
        : id(0), name(std::move(name)), price(price), type(std::move(type)) {}

    // 有参构造函数
    Product::Product(const int id, std::string name, const double price, std::string type)
        : id(id), name(std::move(name)), price(price), type(std::move(type)) {}

    // 获取产品ID
    int Product::getId() const {
        return id;
    }

    // 获取产品名称
    std::string Product::getName() const {
        return name;
    }

    // 获取产品价格
    double Product::getPrice() const {
        return price;
    }

    // 获取产品类型
    std::string Product::getType() const {
        return type;
}
} // namespace pos_system
