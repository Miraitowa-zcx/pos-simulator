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
        std::cout << "2. 收款与找零；\n";
        std::cout << "3. 打印收据；\n";
        std::cout << "0. 退出；\n";
        std::cout << "***********************  end  ***********************\n";
        std::cout << "请输入您的选项：";
        std::cin >> menu;

        switch (menu) {
        case 1:
            {
                std::string name;
                int quantity;

                std::cout << "请输入要选择的商品及数量：";
                std::cin >> name >> quantity;

                // 判断商品是否存在
                std::optional<pos_system::Product> product = inventory.selectProduct(inventory.getProductId(name));
                if (!product) {
                    std::cout << "商品不存在！\n" << std::endl;

                    break;
                }

                if (saleTransaction.saleProduct(product.value(), quantity)) {
                    std::cout << "选择成功！\n";
                    choiceStatus++;
                } else {
                    std::cout << "选择失败！\n";
                }

                break;
            }

        case 2:
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
                    } else {
                        std::cout << "收款失败！\n" << std::endl;
                    }
                } else {
                    std::cout << "收款异常！\n" << std::endl;
                }

                break;
            }

        case 3:
            {
                if (!receiptStatus) {
                    std::cout << "请先支付！\n" << std::endl;
                } else if (!saleTransaction.printReceipt()) {
                    std::cout << "打印失败 " << std::endl;
                }

                break;
            }

        case 0:
            {
                choiceStatus = receiptStatus = 0;
                saleTransaction.clearSale();
            }

            break;

        default:
        std::cout << "输入错误，请重新选择：\n";
        }
    } while (menu++ != 0);
}
