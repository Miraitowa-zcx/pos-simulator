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
        std::cout << "2. ȡ��ѡ��\n";
        std::cout << "3. �տ������㣻\n";
        std::cout << "4. ��ӡ�վݣ�\n";
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
                // ���ѡ��״̬
                if (!choiceStatus) {
                    choiceStatus = receiptStatus = 0;
                    saleTransaction.clearSale();
                }

                std::string name;
                int quantity;
                std::string type;
                std::optional<pos_system::Product> product;

                std::cout << "������Ҫѡ������";
                std::cin >> type;

                // �����Ʒ
                if (!inventory.printInventoryByIds(inventory.getProductType(type))) {
                    std::cout << "��Ʒ�б��쳣��\n" << std::endl;

                    break;
                }

                std::cout << "������Ҫѡ�����Ʒ��������";
                std::cin >> name >> quantity;

                // �ж���Ʒ�Ƿ����
                if (saleTransaction.saleProduct(inventory.selectProduct(inventory.getProductId(name)), quantity)) {
                    std::cout << "ѡ��ɹ���\n";
                    choiceStatus = 1;
                } else {
                    std::cout << "ѡ��ʧ�ܣ�\n";
                }

                break;
            }

        case 2:
            {
                std::string name;
                int quantity;

                if (!choiceStatus) {
                    std::cout << "����ѡ����Ʒ��\n" << std::endl;

                    break;
                }

                std::cout << "������Ҫȡ��ѡ�����Ʒ��������";
                std::cin >> name >> quantity;

                const int cancelStatus =
                    saleTransaction.cancelSale(inventory.selectProduct(inventory.getProductId(name)), quantity);
                if (cancelStatus > 0) {
                    std::cout << "��ȡ��ѡ��\n" << std::endl;
                } else if (cancelStatus == 0) {
                    std::cout << "��ȡ��ѡ��\n" << std::endl;
                    choiceStatus--;
                } else {
                    std::cout << "ȡ��ѡ��ʧ�ܣ�\n" << std::endl;
                }

                break;
            }

        case 3:
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
                        choiceStatus--;
                    } else {
                        std::cout << "�տ�ʧ�ܣ�\n" << std::endl;
                    }
                } else {
                    std::cout << "�տ��쳣��\n" << std::endl;
                }

                break;
            }

        case 4:
            {
                if (!receiptStatus) {
                    std::cout << "����֧����\n" << std::endl;
                } else if (!saleTransaction.printReceipt()) {
                    std::cout << "��ӡʧ�� " << std::endl;
                } else {
                    receiptStatus--;
                }

                break;
            }

        case 0:
            break;

        default:
            std::cout << "�������������ѡ��\n";
        }
    } while (menu++ != 0);
}
