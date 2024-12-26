//
// Created by Miraitowa_zcx on 24-12-23.
//

#include "../include/function/Menu.hpp"

void MainMenu(int& menu) {

    // ��������
    pos_system::Inventory inventory;
    pos_system::SaleTransaction transaction;

    do {
        std::cout << "**********************  ���˵�  **********************\n";
        std::cout << "1. ����Ա���棻\n";
        std::cout << "2. ��Ʒҳ�棻\n";
        std::cout << "3. ��ʾ��棻\n";
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

        if (!inventory.loadProduct()) {
            std::cout << "���ؿ��ʧ�ܣ�\n";
            return;
        }

        switch (menu) {
        case 1:
            {
                system("cls");

                // ����Ա����
                ManagerMenu(menu, inventory);

                break;
            }

        case 2:
            {
                system("cls");

                // ��Ʒҳ��
                VendingMachineMenu(menu, inventory, transaction);

                break;
            }

        case 3:
            {
                // ��ʾ���
                if (!inventory.printInventory()) {
                    std::cout << "��ӡʧ�ܣ�\n";
                }

                break;
            }

        case 0:
            break;

        default:
            std::cout << "�������������ѡ��\n";
        }
    } while (menu != 0);
}
