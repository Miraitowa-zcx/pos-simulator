//
// Created by Miraitowa_zcx on 24-12-23.
//

#include "../include/function/Menu.hpp"

void ManagerMenu(int& menu, pos_system::Inventory& inventory) {

    // 管理员账户及密码
    const static std::string USERNAME = "admin";
    const static std::string PASSWORD = "123456";

    // 输入账户名及密码
    std::string username;
    std::string password;

    std::cout << "请输入账户名：";
    std::cin >> username;
    std::cout << "请输入密码：";
    std::cin >> password;

    // 验证账户名和密码
    if (username != USERNAME || password != PASSWORD) {
        std::cout << "用户名或密码错误！\n" << std::endl;
        return;
    }

    std::cout << "欢迎 " << username << " 登录！\n";

    do {
        std::cout << "**********************  管理菜单  **********************\n";
        std::cout << "1. 添加商品；\n";
        std::cout << "2. 更新商品；\n";
        std::cout << "3. 删除商品；\n";
        std::cout << "4. 查询商品；\n";
        std::cout << "0. 退出；\n";
        std::cout << "***********************  end  ***********************\n";
        std::cout << "请输入您的选项：";
        std::cin >> menu;

        switch (menu) {
        case 1:
            {
                // 添加商品

                std::string name;
                double price;
                int quantity;

                std::cout << "请输入商品名称和价格及数量：";
                std::cin >> name >> price >> quantity;

                if (const int id = inventory.addProduct(pos_system::Product(name, price), quantity)) {
                    if (id == -1) {
                        std::cout << "产品名称已存在: " << "  " << std::endl;
                    } else if (!inventory.saveProduct(id)) {
                        std::cout << "添加失败！\n";
                    } else {
                        std::cout << "添加成功！\n";
                    }
                } else {
                    std::cout << "商品异常！\n";
                }

                break;
            }

        case 2:
            {
                // 更新商品

                std::string name;
                double price;
                int quantity;

                std::cout << "请输入要更新的商品：";
                std::cin >> name;
                std::cout << "请输入商品名称和价格及数量：";
                std::cin >> name >> price >> quantity;

                if (const int id = inventory.updateProduct(
                        inventory.getProductId(name), pos_system::Product(name, price), quantity)) {
                    if (!inventory.saveProduct(id)) {
                        std::cout << "更新失败！\n";
                    } else {
                        std::cout << "更新成功！\n";
                    }
                } else {
                    std::cout << "产品名称不存在: " << "  " << std::endl;
                }

                break;
            }

        case 3:
            {
                // 删除商品

                std::string name;

                std::cout << "请输入要删除的商品：";
                std::cin >> name;

                if (const int id = inventory.deleteProduct(inventory.getProductId(name))) {
                    if (!inventory.saveProduct(id)) {
                        std::cout << "删除失败！\n";
                    } else {
                        std::cout << "删除成功！\n";
                    }
                } else {
                    std::cout << "产品名称不存在: " << "  " << std::endl;
                }

                break;
            }

        case 4:
            {
                // 查询商品

                std::string name;

                std::cout << "请输入要查询的商品：";
                std::cin >> name;

                if (const std::optional<pos_system::Product> product =
                        inventory.selectProduct(inventory.getProductId(name))) {
                    if (!inventory.saveProduct(product->getId())) {
                        std::cout << "查询失败！\n";
                    } else {
                        std::cout << "商品名称: " << product->getName() << "  " << std::endl;
                        std::cout << "商品价格: " << product->getPrice() << "元  " << std::endl;
                        std::cout << "商品数量: " << inventory.getProductQuantity(product->getId()) << "  "
                                  << std::endl;
                        std::cout << "查询成功！\n";
                    }
                } else {
                    std::cout << "产品名称不存在: " << "  " << std::endl;
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
