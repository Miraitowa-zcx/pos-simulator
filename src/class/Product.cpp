//
// Created by Miraitowa_zcx on 24-12-23.
//

#include "../include/class/Product.hpp"

namespace pos_system {

    // �޲ι��캯��
    Product::Product() : id(0), price(0.0) {}

    // �вι��캯��
    Product::Product(std::string name, const double price, std::string type)
        : id(0), name(std::move(name)), price(price), type(std::move(type)) {}

    // �вι��캯��
    Product::Product(const int id, std::string name, const double price, std::string type)
        : id(id), name(std::move(name)), price(price), type(std::move(type)) {}

    // ��ȡ��ƷID
    int Product::getId() const {
        return id;
    }

    // ��ȡ��Ʒ����
    std::string Product::getName() const {
        return name;
    }

    // ��ȡ��Ʒ�۸�
    double Product::getPrice() const {
        return price;
    }

    // ��ȡ��Ʒ����
    std::string Product::getType() const {
        return type;
}
} // namespace pos_system
