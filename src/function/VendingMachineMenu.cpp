//
// Created by Miraitowa_zcx on 24-12-23.
//

#include "../include/function/Menu.hpp"

void VendingMachineMenu(int& menu, pos_system::Inventory& inventory, pos_system::SaleTransaction& saleTransaction) {

    // ״̬����
    int choiceStatus = 0, receiptStatus = 0;

    do {
        std::cout << "**********************  �ۻ����˵�  **********************\n";
        std::cout << "1. ��Ʒѡ��\n";
        std::cout << "2. �տ������㣻\n";
        std::cout << "3. ��ӡ�վݣ�\n";
        std::cout << "0. �˳���\n";
        std::cout << "***********************  end  ***********************\n";
        std::cout << "����������ѡ�";
        std::cin >> menu;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "������Ч��������һ�����֡�\n";

            menu = 999;
        }

        switch (menu) {
        case 1:
            {
                std::string name;
                int quantity;
                std::string type;
                std::optional<pos_system::Product> product;

                std::cout << "������Ҫѡ������";
                std::cin >> type;

                const std::vector<int> ids = inventory.getProductType(type);
                if (ids.empty()) {
                    std::cout << "��𲻴��ڣ�\n" << std::endl;

                    break;
                }

                std::cout << std::left << std::setw(5) << "ID" << std::setw(20) << "����" << std::setw(10) << "�۸�"
                          << std::setw(10) << "����" << std::setw(5) << "����"
                          << "\n";
                for (const int id : ids) {
                    product = inventory.selectProduct(id);
                    if (product) {
                        std::cout << std::left << std::setw(5) << product->getId() << std::setw(20)
                                  << product->getName() << std::setw(10) << product->getPrice() << std::setw(10)
                                  << product->getType() << std::setw(5)
                                  << inventory.getProductQuantity(product->getId()) << "\n";
                    }
                }

                std::cout << "������Ҫѡ�����Ʒ��������";
                std::cin >> name >> quantity;

                // �ж���Ʒ�Ƿ����
                product = inventory.selectProduct(inventory.getProductId(name));
                if (!product) {
                    std::cout << "��Ʒ�����ڣ�\n" << std::endl;

                    break;
                }

                if (saleTransaction.saleProduct(product.value(), quantity)) {
                    std::cout << "ѡ��ɹ���\n";
                    choiceStatus++;
                } else {
                    std::cout << "ѡ��ʧ�ܣ�\n";
                }

                break;
            }

        case 2:
            {
                int pricePayable;

                if (!choiceStatus) {
                    std::cout << "����ѡ����Ʒ��\n" << std::endl;

                    break;
                }

                std::cout << "�븶�";
                std::cin >> pricePayable;

                if (saleTransaction.finalizeSale(inventory, pricePayable)) {
                    if (inventory.saveProduct(-1)) {
                        std::cout << "�տ�ɹ���\n" << std::endl;
                        receiptStatus++;
                    } else {
                        std::cout << "�տ�ʧ�ܣ�\n" << std::endl;
                    }
                } else {
                    std::cout << "�տ��쳣��\n" << std::endl;
                }

                break;
            }

        case 3:
            {
                if (!receiptStatus) {
                    std::cout << "����֧����\n" << std::endl;
                } else if (!saleTransaction.printReceipt()) {
                    std::cout << "��ӡʧ�� " << std::endl;
                }

                break;
            }

        case 0:
            {
                choiceStatus = receiptStatus = 0;
                saleTransaction.clearSale();

                break;
            }

        default:
            std::cout << "�������������ѡ��\n";
        }
    } while (menu++ != 0);
}
