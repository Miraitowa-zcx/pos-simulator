//
// Created by Miraitowa_zcx on 24-12-23.
//

#include "../include/function/Menu.hpp"

void VendingMachineMenu(int& menu, pos_system::Inventory& inventory, pos_system::SaleTransaction& saleTransaction) {

    // 状态变量
    int choiceStatus = 0, receiptStatus = 0;

    do {
        std::cout << "**********************  售货机菜单  **********************\n";
        std::cout << "1. 商品选择；\n";
        std::cout << "2. 取消选择\n";
        std::cout << "3. 收款与找零；\n";
        std::cout << "4. 打印收据；\n";
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

        switch (menu) {
        case 1:
            {
                // 清除选择状态
                if (!choiceStatus) {
                    choiceStatus = receiptStatus = 0;
                    saleTransaction.clearSale();
                }

                std::string name;
                int quantity;
                std::string type;
                std::optional<pos_system::Product> product;

                std::cout << "请输入要选择的类别：";
                std::cin >> type;

                // 输出商品
                if (!inventory.printInventoryByIds(inventory.getProductType(type))) {
                    std::cout << "商品列表异常！\n" << std::endl;

                    break;
                }

                std::cout << "请输入要选择的商品及数量：";
                std::cin >> name >> quantity;

                // 判断商品是否存在
                if (saleTransaction.saleProduct(inventory.selectProduct(inventory.getProductId(name)), quantity)) {
                    std::cout << "选择成功！\n";
                    choiceStatus = 1;
                } else {
                    std::cout << "选择失败！\n";
                }

                break;
            }

        case 2:
            {
                std::string name;
                int quantity;

                if (!choiceStatus) {
                    std::cout << "请先选择商品！\n" << std::endl;

                    break;
                }

                std::cout << "请输入要取消选择的商品及数量：";
                std::cin >> name >> quantity;

                const int cancelStatus =
                    saleTransaction.cancelSale(inventory.selectProduct(inventory.getProductId(name)), quantity);
                if (cancelStatus > 0) {
                    std::cout << "已取消选择！\n" << std::endl;
                } else if (cancelStatus == 0) {
                    std::cout << "已取消选择！\n" << std::endl;
                    choiceStatus--;
                } else {
                    std::cout << "取消选择失败！\n" << std::endl;
                }

                break;
            }

        case 3:
            {
                int pricePayable;

                if (!choiceStatus) {
                    std::cout << "请先选择商品！\n" << std::endl;

                    break;
                }

                std::cout << "请付款：";
                std::cin >> pricePayable;

                if (saleTransaction.finalizeSale(inventory, pricePayable)) {
                    if (inventory.saveProduct(-1)) {
                        std::cout << "收款成功！\n" << std::endl;
                        receiptStatus++;
                        choiceStatus--;
                    } else {
                        std::cout << "收款失败！\n" << std::endl;
                    }
                } else {
                    std::cout << "收款异常！\n" << std::endl;
                }

                break;
            }

        case 4:
            {
                if (!receiptStatus) {
                    std::cout << "请先支付！\n" << std::endl;
                } else if (!saleTransaction.printReceipt()) {
                    std::cout << "打印失败 " << std::endl;
                } else {
                    receiptStatus--;
                }

                break;
            }

        case 0:
            break;

        default:
            std::cout << "输入错误，请重新选择：\n";
        }
    } while (menu++ != 0);
}
