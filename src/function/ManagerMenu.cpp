//
// Created by Miraitowa_zcx on 24-12-23.
//

#include "../include/function/Menu.hpp"

void ManagerMenu(int& menu, pos_system::Inventory& inventory) {

    // ����Ա�˻�������
    const static std::string USERNAME = "admin";
    const static std::string PASSWORD = "123456";

    // �����˻���������
    std::string username;
    std::string password;

    std::cout << "�������˻�����";
    std::cin >> username;
    std::cout << "���������룺";
    std::cin >> password;

    // ��֤�˻���������
    if (username != USERNAME || password != PASSWORD) {
        std::cout << "�û������������\n" << std::endl;
        return;
    }

    std::cout << "��ӭ " << username << " ��¼��\n";

    do {
        std::cout << "**********************  ����˵�  **********************\n";
        std::cout << "1. �����Ʒ��\n";
        std::cout << "2. ������Ʒ��\n";
        std::cout << "3. ɾ����Ʒ��\n";
        std::cout << "4. ��ѯ��Ʒ��\n";
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
                // �����Ʒ

                std::string name;
                double price;
                std::string type;
                int quantity;

                std::cout << "��������Ʒ���ơ��۸����������";
                std::cin >> name >> price >> type >> quantity;

                if (const int id = inventory.addProduct(pos_system::Product(name, price, type), quantity)) {
                    if (id == -1) {
                        std::cout << "��Ʒ�����Ѵ���: " << "  " << std::endl;
                    } else if (!inventory.saveProduct(id)) {
                        std::cout << "���ʧ�ܣ�\n" << std::endl;
                    } else {
                        std::cout << "��ӳɹ���\n" << std::endl;
                    }
                } else {
                    std::cout << "��Ʒ�쳣��\n" << std::endl;
                }

                break;
            }

        case 2:
            {
                // ������Ʒ

                std::string name;
                double price;
                std::string type;
                int quantity;

                std::cout << "������Ҫ���µ���Ʒ��";
                std::cin >> name;
                std::cout << "��������Ʒ���ơ��۸����������";
                std::cin >> name >> price >> type >> quantity;

                if (const int id = inventory.updateProduct(
                        inventory.getProductId(name), pos_system::Product(name, price, type), quantity)) {
                    if (!inventory.saveProduct(id)) {
                        std::cout << "����ʧ�ܣ�\n";
                    } else {
                        std::cout << "���³ɹ���\n";
                    }
                } else {
                    std::cout << "��Ʒ���Ʋ�����: " << "  " << std::endl;
                }

                break;
            }

        case 3:
            {
                // ɾ����Ʒ

                std::string name;

                std::cout << "������Ҫɾ������Ʒ��";
                std::cin >> name;

                if (const int id = inventory.deleteProduct(inventory.getProductId(name))) {
                    if (!inventory.saveProduct(id)) {
                        std::cout << "ɾ��ʧ�ܣ�\n";
                    } else {
                        std::cout << "ɾ���ɹ���\n";
                    }
                } else {
                    std::cout << "��Ʒ���Ʋ�����: " << "  " << std::endl;
                }

                break;
            }

        case 4:
            {
                // ��ѯ��Ʒ

                std::string name;

                std::cout << "������Ҫ��ѯ����Ʒ���ƣ�";
                std::cin >> name;

                if (const std::optional<pos_system::Product> product =
                        inventory.selectProduct(inventory.getProductId(name))) {
                    if (!inventory.saveProduct(product->getId())) {
                        std::cout << "��ѯʧ�ܣ�\n";
                    } else {
                        std::cout << "��Ʒ����: " << product->getName() << "  " << std::endl;
                        std::cout << "��Ʒ�۸�: " << product->getPrice() << "Ԫ  " << std::endl;
                        std::cout << "��Ʒ���: " << product->getType() << "  " << std::endl;
                        std::cout << "��Ʒ����: " << inventory.getProductQuantity(product->getId()) << "  "
                                  << std::endl;
                        std::cout << "��ѯ�ɹ���\n";
                    }
                } else {
                    std::cout << "��Ʒ���Ʋ�����: " << "  " << std::endl;
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
