//
// Created by Miraitowa_zcx on 24-12-23.
//

#ifndef MENU_HPP
#define MENU_HPP

#include "../class/SaleTransaction.hpp"

// ���˵�
void MainMenu(int& menu);

// ����Ա�˵�
void ManagerMenu(int& menu, pos_system::Inventory& inventory);

// �ۻ����˵�
void VendingMachineMenu(int& menu, pos_system::Inventory& inventory, pos_system::SaleTransaction& saleTransaction);

#endif // MENU_HPP
