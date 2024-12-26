//
// Created by Miraitowa_zcx on 24-12-23.
//

#include "../include/class/SaleTransaction.hpp"

namespace pos_system {
    // �������
    int SaleTransaction::saleProduct(const Product& product, int quantity) {
        // ���items �д���һ��Product ��������������������������һ������Ŀ
        if (std::ranges::find_if(items,
                [&product](const std::pair<Product, int>& item) { return item.first.getId() == product.getId(); })
            != items.end()) {
            // ��������
            for (auto& [fst, snd] : items) {
                if (fst.getId() == product.getId()) {
                    snd += quantity;
                    total += product.getPrice() * quantity;
                    break;
                }
            }
        } else {
            // �������Ŀ
            items.emplace_back(product, quantity);
            total += product.getPrice() * quantity;
        }
        return true;
    }

    // �ύ����
    int SaleTransaction::finalizeSale(Inventory& inventory, const int pricePayable) {
        // �ж�֧������Ƿ��㹻
        if (pricePayable < total) {
            std::cout << "֧�����㣡��Ҫ " << total << "Ԫ����ֻ֧���� " << pricePayable << "Ԫ\n";
            return false;
        }
        // ���ٿ��
        for (auto& [product, quantitySold] : items) {
            // �жϿ���Ƿ��㹻
            if (const int currentQuantity = inventory.getProductQuantity(product.getId());
                currentQuantity >= quantitySold) {
                // ���¿��
                if (const int newQuantity = currentQuantity - quantitySold;
                    inventory.updateProduct(product.getId(), product, newQuantity)) {
                    std::cout << "���� " << quantitySold << "�� " << product.getName() << " �ɹ���\n";
                } else {
                    std::cout << "���� " << quantitySold << "�� " << product.getName() << " ʧ�ܣ�\n";
                    return false;
                }
            } else {
                std::cout << "���� " << quantitySold << "�� " << product.getName() << " ��治�㣡\n";
                return false;
            }
        }

        // ��ӡ����
        const double change = pricePayable - total;
        std::cout << "�ܼۣ�" << total << "Ԫ\n";
        std::cout << "֧����" << pricePayable << "Ԫ\n";
        std::cout << "���㣺" << change << "Ԫ\n";

        return true;
    }

    // ��ӡ����
    int SaleTransaction::printReceipt() {
        std::cout << "�վݣ�\n";
        for (const auto& [fst, snd] : items) {
            std::cout << fst.getName() << " x" << snd << "�� " << std::fixed << std::setprecision(2)
                      << fst.getPrice() * snd << "Ԫ\n";
        }
        std::cout << "�ܼۣ�" << total << "Ԫ\n";

        return true;
    }

    // �������
    int SaleTransaction::clearSale() {
        items.clear();
        total = 0.0;

        return true;
    }
} // namespace pos_system
