//
// Created by Miraitowa_zcx on 24-12-23.
//

#include "../include/class/Inventory.hpp"

namespace pos_system {
    // 构造函数
    Inventory::Inventory() : currentId(0) {
        // 初始化 当前 ID
        if (std::ifstream file("data/product.csv"); file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                std::stringstream ss(line);
                int id;
                ss >> id;
                if (id >= currentId) {
                    currentId = id + 1;
                }
            }
        }

        if (currentId == 0) {
            currentId++;
        }
    }

    // 保存商品
    bool Inventory::saveProduct(int id) {
        std::filesystem::create_directory("data");
        const std::string filename = "data/product.csv";

        // 读取文件内容到临时容器
        std::vector<std::string> lines;
        if (std::ifstream infile(filename); infile.is_open()) {
            std::string line;
            while (std::getline(infile, line)) {
                lines.push_back(line);
            }
            infile.close();
        }
        // 如果 id 为 -1，则保存所有产品
        if (id == -1) {
            lines.clear(); // 清空现有内容
            for (const auto& [product_id, product_data] : products) {
                const auto& [fst, snd] = product_data;
                lines.push_back(std::to_string(product_id) + "," + fst.getName() + "," + std::to_string(fst.getPrice())
                                + "," + std::to_string(snd));
            }
        } else {
            // 找到并更新指定行
            bool found = false;
            for (auto& line : lines) {
                std::istringstream iss(line);
                if (std::string token; std::getline(iss, token, ',')) {
                    try {
                        if (int lineId = std::stoi(token); lineId == id) {
                            found                  = true;
                            const auto& [fst, snd] = products[id];
                            line = std::to_string(id) + "," + fst.getName() + "," + std::to_string(fst.getPrice()) + ","
                                 + std::to_string(snd);
                            break;
                        }
                    } catch ([[maybe_unused]] const std::invalid_argument& e) {
                        std::cout << "无效的整数转换: " << token << std::endl;
                    } catch ([[maybe_unused]] const std::out_of_range& e) {
                        std::cout << "整数超出范围: " << token << std::endl;
                    }
                }
            }

            // 如果没有找到指定的 id，则添加新行
            if (!found) {
                const auto& [fst, snd] = products[id];
                lines.push_back(std::to_string(id) + "," + fst.getName() + "," + std::to_string(fst.getPrice()) + ","
                                + std::to_string(snd));
            }
        }

        // 写回文件
        std::ofstream file(filename, std::ios::trunc); // 使用 trunc 模式清空文件
        if (!file.is_open()) {
            std::cout << "无法打开文件进行写入。" << std::endl;
            return false;
        }

        // 写入文件
        for (const auto& line : lines) {
            file << line << "\n";
            if (!file) {
                std::cout << "写入文件时发生错误。" << std::endl;
                file.close();
                return false;
            }
        }

        file.close();
        return true;
    }

    // 加载商品
    bool Inventory::loadProduct() {
        std::filesystem::create_directory("data");
        std::ifstream file("data/product.csv");
        // 如果文件不存在，则创建一个空的文件
        if (!std::filesystem::exists("data/product.csv")) {
            std::ofstream outfile("data/product.csv");
            outfile.close();
            return true;
        }
        if (!file.is_open()) {
            std::cout << "无法打开文件进行读取。" << std::endl;
            return false;
        }

        // 读取文件内容
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string token;
            std::vector<std::string> tokens;

            // 去除空格
            while (std::getline(ss, token, ',')) {
                tokens.push_back(token);
            }

            // 去除前后空格
            for (auto& t : tokens) {
                t.erase(0, t.find_first_not_of(" \t\n\r\f\v"));
                t.erase(t.find_last_not_of(" \t\n\r\f\v") + 1);
            }

            // 提取数据
            int id           = std::stoi(tokens[0]);
            std::string name = tokens[1];
            double price     = std::stod(tokens[2]);
            int quantity     = std::stoi(tokens[3]);

            // 添加到容器中
            products[id]           = std::make_pair(Product(id, name, price), quantity);
            nameToIdMap[tokens[1]] = id;

            // 更新当前 ID
            if (id >= currentId) {
                currentId = id + 1;
            }
        }
        file.close();
        return true;
    }

    // 添加商品
    int Inventory::addProduct(const Product& product, int quantity) {
        // 检查是否已存在相同名称的产品
        for (const auto& [fst, snd] : products | std::views::values) {
            if (fst.getName() == product.getName()) {
                return -1; // 如果找到相同名称的产品，返回 -1
            }
        }

        const int newId = currentId++;
        // 添加到容器中
        products[newId] = std::make_pair(Product(newId, product.getName(), product.getPrice()), quantity);
        nameToIdMap[product.getName()] = newId;
        return newId;
    }

    // 更新商品
    int Inventory::updateProduct(const int productId, const Product& product, const int quantity) {
        if (products.contains(productId)) {
            // 更新容器和映射
            products[productId] = std::make_pair(Product(productId, product.getName(), product.getPrice()), quantity);
            nameToIdMap[product.getName()] = productId;
            return productId;
        }
        return false;
    }

    // 删除商品
    int Inventory::deleteProduct(const int productId) {
        if (products.erase(productId)) {
            // 删除映射
            nameToIdMap.erase(products[productId].first.getName());
            return productId;
        }
        return false;
    }

    // 查询商品
    std::optional<Product> Inventory::selectProduct(const int productId) const {
        // 查找商品
        if (const auto it = products.find(productId); it != products.end()) {
            return it->second.first;
        }
        return std::nullopt;
    }

    // 获取商品 ID
    int Inventory::getProductId(const std::string& productName) const {
        if (const auto it = nameToIdMap.find(productName); it != nameToIdMap.end()) {
            return it->second;
        }
        return -1;
    }

    // 获取商品数量
    int Inventory::getProductQuantity(const int productId) const {
        if (const auto it = products.find(productId); it != products.end()) {
            return it->second.second;
        }
        return 0;
    }

    // 打印库存
    int Inventory::printInventory() const {
        std::cout << "ID\t名称\t价格\t数量\n";
        for (const auto& [fst, snd] : products) {
            if (snd.first.getName().empty()) {
                continue; // 跳过名称为 "0" 的产品
            }
            std::cout << fst << "\t" << snd.first.getName() << "\t" << std::fixed << std::setprecision(2)
                      << snd.first.getPrice() << "\t" << snd.second << "\n";
        }
        return true;
    }
} // namespace pos_system
