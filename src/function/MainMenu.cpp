//
// Created by Miraitowa_zcx on 24-12-23.
//

#include "../include/function/Menu.hpp"

void MainMenu(int& menu) {

    // 创建对象
    pos_system::Inventory inventory;
    pos_system::SaleTransaction transaction;

    do {
        std::cout << "**********************  主菜单  **********************\n";
        std::cout << "1. 管理员界面；\n";
        std::cout << "2. 商品页面；\n";
        std::cout << "3. 显示库存；\n";
        std::cout << "0. 退出；\n";
        std::cout << "***********************  end  ***********************\n";
        std::cout << "请输入您的选项：";
        std::cin >> menu;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "输入无效，请输入一个数字。\n";

            menu = 999;
        }

        if (!inventory.loadProduct()) {
            std::cout << "加载库存失败！\n";
            return;
        }

        switch (menu) {
        case 1:
            {
                system("cls");

                // 管理员界面
                ManagerMenu(menu, inventory);

                break;
            }

        case 2:
            {
                system("cls");

                // 商品页面
                VendingMachineMenu(menu, inventory, transaction);

                break;
            }

        case 3:
            {
                // 显示库存
                if (!inventory.printInventory()) {
                    std::cout << "打印失败！\n";
                }

                break;
            }

        case 0:
            break;

        default:
            std::cout << "输入错误，请重新选择：\n";
        }
    } while (menu != 0);
}
