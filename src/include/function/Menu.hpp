//
// Created by Miraitowa_zcx on 24-12-23.
//

#ifndef MENU_HPP
#define MENU_HPP

#include <cstdlib>
#include <iostream>

#include "../class/Inventory.hpp"
#include "../class/SaleTransaction.hpp"

// 主菜单
void MainMenu(int& menu);

// 管理员菜单
void ManagerMenu(int& menu, pos_system::Inventory& inventory);

// 售货机菜单
void VendingMachineMenu(int& menu, pos_system::Inventory& inventory, pos_system::SaleTransaction& saleTransaction);

#endif // MENU_HPP
