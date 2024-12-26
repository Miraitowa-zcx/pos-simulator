//
// Created by Miraitowa_zcx on 24-12-23.
//

#include "../include/class/SaleTransaction.hpp"

namespace pos_system {
    // 添加销售
    int SaleTransaction::saleProduct(const std::optional<Product>& product, int quantity) {
        // 判断商品是否存在
        if (!product.has_value()) {
            return false;
        }
        // 如果items 中存在一个Product 和数量，则更新数量，否则添加一个新条目
        if (std::ranges::find_if(items,
                [&product](
                    const std::pair<Product, int>& item) { return item.first.getId() == product.value().getId(); })
            != items.end()) {
            // 更新数量
            for (auto& [fst, snd] : items) {
                if (fst.getId() == product.value().getId()) {
                    snd += quantity;
                    total += product.value().getPrice() * quantity;
                    break;
                }
            }
        } else {
            // 添加新条目
            items.emplace_back(product.value(), quantity);
            total += product.value().getPrice() * quantity;
        }
        return true;
    }

    // 取消销售
    int SaleTransaction::cancelSale(const std::optional<Product>& product, const int quantity) {
        if (!product.has_value()) {
            return -1;
        }

        // 判断商品是否存在
        const auto it = std::ranges::find_if(items,
            [&product](const std::pair<Product, int>& item) { return item.first.getId() == product.value().getId(); });

        if (it != items.end()) {
            // 判断数量是否足够
            if (const int realQuantity = it->second; quantity <= realQuantity) {
                total -= quantity * product.value().getPrice();
                items.erase(it);
                if(realQuantity - realQuantity != 0) {
items.emplace_back(product.value(), realQuantity - quantity);
																						} 

                return realQuantity - realQuantity;
            }
            return -1;
        }
        return -1;
    }

    // 提交销售
    int SaleTransaction::finalizeSale(Inventory& inventory, const int pricePayable) {
        // 判断支付金额是否足够
        if (pricePayable < total) {
            std::cout << "支付金额不足！需要 " << total << "元，但只支付了 " << pricePayable << "元\n";
            return false;
        }
        // 减少库存
        for (auto& [product, quantitySold] : items) {
            // 判断库存是否足够
            if (const int currentQuantity = inventory.getProductQuantity(product.getId());
                currentQuantity >= quantitySold) {
                // 更新库存
                if (const int newQuantity = currentQuantity - quantitySold;
                    inventory.updateProduct(product.getId(), product, newQuantity)) {
                    std::cout << "出售 " << quantitySold << "个 " << product.getName() << " 成功！\n";
                } else {
                    std::cout << "出售 " << quantitySold << "个 " << product.getName() << " 失败！\n";
                    return false;
                }
            } else {
                std::cout << "出售 " << quantitySold << "个 " << product.getName() << " 库存不足！\n";
                return false;
            }
        }

        // 打印销售
        const double change = pricePayable - total;
        std::cout << "总价：" << total << "元\n";
        std::cout << "支付金额：" << pricePayable << "元\n";
        std::cout << "找零：" << change << "元\n";

        return true;
    }

    // 打印销售
    int SaleTransaction::printReceipt() {
        std::cout << "收据：\n";
        for (const auto& [fst, snd] : items) {
            std::cout << fst.getName() << " x" << snd << "： " << std::fixed << std::setprecision(2)
                      << fst.getPrice() * snd << "元\n";
        }
        std::cout << "总价：" << total << "元\n";

        return true;
    }

    // 清空销售
    int SaleTransaction::clearSale() {
        items.clear();
        total = 0.0;

        return true;
    }
} // namespace pos_system
