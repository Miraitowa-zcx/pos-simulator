//
// Created by Miraitowa_zcx on 24-12-23.
//

#include "../include/class/Inventory.hpp"

namespace pos_system {
    // ���캯��
    Inventory::Inventory() : currentId(0) {
        // ��ʼ�� ��ǰ ID
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

    // ������Ʒ
    bool Inventory::saveProduct(int id) {
        std::filesystem::create_directory("data");
        const std::string filename = "data/product.csv";

        // ��ȡ�ļ����ݵ���ʱ����
        std::vector<std::string> lines;
        if (std::ifstream infile(filename); infile.is_open()) {
            std::string line;
            while (std::getline(infile, line)) {
                lines.push_back(line);
            }
            infile.close();
        }
        // ��� id Ϊ -1���򱣴����в�Ʒ
        if (id == -1) {
            lines.clear(); // �����������
            for (const auto& [product_id, product_data] : products) {
                const auto& [fst, snd] = product_data;
                lines.push_back(std::to_string(product_id) + "," + fst.getName() + "," + std::to_string(fst.getPrice())
                                + "," + fst.getType() + "," + std::to_string(snd));
            }
        } else {
            // �ҵ�������ָ����
            bool found = false;
            for (auto& line : lines) {
                std::istringstream iss(line);
                if (std::string token; std::getline(iss, token, ',')) {
                    try {
                        if (int lineId = std::stoi(token); lineId == id) {
                            found                  = true;
                            const auto& [fst, snd] = products[id];
                            line = std::to_string(id) + "," + fst.getName() + "," + std::to_string(fst.getPrice()) + ","
                                 + fst.getType() + "," + std::to_string(snd);
                            break;
                        }
                    } catch ([[maybe_unused]] const std::invalid_argument& e) {
                        std::cout << "��Ч������ת��: " << token << std::endl;
                    } catch ([[maybe_unused]] const std::out_of_range& e) {
                        std::cout << "����������Χ: " << token << std::endl;
                    }
                }
            }

            // ���û���ҵ�ָ���� id�����������
            if (!found) {
                const auto& [fst, snd] = products[id];
                lines.push_back(std::to_string(id) + "," + fst.getName() + "," + std::to_string(fst.getPrice()) + ","
                                + fst.getType() + "," + std::to_string(snd));
            }
        }

        // д���ļ�
        std::ofstream file(filename, std::ios::trunc); // ʹ�� trunc ģʽ����ļ�
        if (!file.is_open()) {
            std::cout << "�޷����ļ�����д�롣" << std::endl;
            return false;
        }

        // д���ļ�
        for (const auto& line : lines) {
            file << line << "\n";
            if (!file) {
                std::cout << "д���ļ�ʱ��������" << std::endl;
                file.close();
                return false;
            }
        }

        file.close();
        return true;
    }

    // ������Ʒ
    bool Inventory::loadProduct() {
        std::filesystem::create_directory("data");
        std::ifstream file("data/product.csv");
        // ����ļ������ڣ��򴴽�һ���յ��ļ�
        if (!std::filesystem::exists("data/product.csv")) {
            std::ofstream outfile("data/product.csv");
            outfile.close();
            return true;
        }
        if (!file.is_open()) {
            std::cout << "�޷����ļ����ж�ȡ��" << std::endl;
            return false;
        }

        // ��ȡ�ļ�����
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string token;
            std::vector<std::string> tokens;

            // ȥ���ո�
            while (std::getline(ss, token, ',')) {
                tokens.push_back(token);
            }

            // ȥ��ǰ��ո�
            for (auto& t : tokens) {
                t.erase(0, t.find_first_not_of(" \t\n\r\f\v"));
                t.erase(t.find_last_not_of(" \t\n\r\f\v") + 1);
            }

            // ��ȡ����
            int id           = std::stoi(tokens[0]);
            std::string name = tokens[1];
            double price     = std::stod(tokens[2]);
            std::string type = tokens[3];
            int quantity     = std::stoi(tokens[4]);

            // ��ӵ�������
            products[id]           = std::make_pair(Product(id, name, price, type), quantity);
            nameToIdMap[tokens[1]] = id;
            typeToIdMap[tokens[3]] = id;

            // ���µ�ǰ ID
            if (id >= currentId) {
                currentId = id + 1;
            }
        }
        file.close();
        return true;
    }

    // �����Ʒ
    int Inventory::addProduct(const Product& product, int quantity) {
        // ����Ƿ��Ѵ�����ͬ���ƵĲ�Ʒ
        for (const auto& [fst, snd] : products | std::views::values) {
            if (fst.getName() == product.getName()) {
                return -1; // ����ҵ���ͬ���ƵĲ�Ʒ������ -1
            }
        }

        const int newId = currentId++;
        // ��ӵ�������
        products[newId] =
            std::make_pair(Product(newId, product.getName(), product.getPrice(), product.getType()), quantity);
        nameToIdMap[product.getName()] = newId;
        typeToIdMap[product.getType()] = newId;
        return newId;
    }

    // ������Ʒ
    int Inventory::updateProduct(const int productId, const Product& product, const int quantity) {
        if (products.contains(productId)) {
            // ����������ӳ��
            products[productId] =
                std::make_pair(Product(productId, product.getName(), product.getPrice(), product.getType()), quantity);
            nameToIdMap[product.getName()] = productId;
            typeToIdMap[product.getType()] = productId;
            return productId;
        }
        return false;
    }

    // ɾ����Ʒ
    int Inventory::deleteProduct(const int productId) {
        if (products.erase(productId)) {
            // ɾ��ӳ��
            nameToIdMap.erase(products[productId].first.getName());
            typeToIdMap.erase(products[productId].first.getType());
            return productId;
        }
        return false;
    }

    // ��ѯ��Ʒ
    std::optional<Product> Inventory::selectProduct(const int productId) const {
        // ��� ID Ϊ -1���򷵻ؿ�
        if (productId == -1) {
            return std::nullopt;
        }

        // ������Ʒ
        if (const auto it = products.find(productId); it != products.end()) {
            return it->second.first;
        }
        return std::nullopt;
    }

    // ��ȡ��Ʒ ID
    int Inventory::getProductId(const std::string& productName) const {
        if (const auto it = nameToIdMap.find(productName); it != nameToIdMap.end()) {
            return it->second;
        }
        return -1;
    }

    // ���� ID ��ȡ��Ʒ����
    std::vector<int> Inventory::getProductType(const std::string& productType) {
        std::vector<int> ids;
        for (const auto& [fst, snd] : products) {
            if (snd.first.getType() == productType) {
                ids.push_back(fst);
            }
        }
        return ids;
    }

    // ��ȡ��Ʒ����
    int Inventory::getProductQuantity(const int productId) const {
        if (const auto it = products.find(productId); it != products.end()) {
            return it->second.second;
        }
        return 0;
    }

    // ��ӡ���
    int Inventory::printInventory() const {
        std::cout << std::left << std::setw(5) << "ID" << std::setw(20) << "����" << std::setw(10) << "�۸�"
                  << std::setw(10) << "����" << std::setw(5) << "����"
                  << "\n";
        for (const auto& [fst, snd] : products) {
            if (snd.first.getName().empty()) {
                continue; // ��������Ϊ �� ����Ʒ
            }
            std::cout << std::left << std::setw(5) << fst << std::setw(20) << snd.first.getName() << std::setw(10)
                      << std::fixed << std::setprecision(2) << snd.first.getPrice() << std::setw(10)
                      << snd.first.getType() << std::setw(5) << snd.second << "\n";
        }
        return true;
    }

    int Inventory::printInventoryByIds(const std::vector<int>& ids) const {
        // �������Ƿ����
        if (ids.empty()) {
            std::cout << "��𲻴��ڣ�\n" << std::endl;

            return false;
        }

        std::cout << std::left << std::setw(5) << "ID" << std::setw(20) << "����" << std::setw(10) << "�۸�"
                  << std::setw(10) << "����" << std::setw(5) << "����"
                  << "\n";
        // ���� ID �б�
        for (const auto& id : ids) {
            // ������Ʒ
            if (const auto it = products.find(id); it != products.end()) {
                std::cout << std::left << std::setw(5) << it->first << std::setw(20) << it->second.first.getName()
                          << std::setw(10) << std::fixed << std::setprecision(2) << it->second.first.getPrice()
                          << std::setw(10)<< it->second.first.getType() << std::setw(5) << it->second.second << "\n";
            }
        }
        return true;
    }
} // namespace pos_system
