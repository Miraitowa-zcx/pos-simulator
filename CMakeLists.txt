cmake_minimum_required(VERSION 3.29)
project(pos-simulator)

set(CMAKE_CXX_STANDARD 26)

add_executable(
        pos-simulator
        src/main.cpp
        src/include/function/Menu.hpp
        src/function/MainMenu.cpp
        src/function/ManagerMenu.cpp
        src/function/VendingMachineMenu.cpp
        src/include/class/Product.hpp
        src/class/Product.cpp
        src/include/class/Inventory.hpp
        src/class/Inventory.cpp
        src/include/class/SaleTransaction.hpp
        src/class/SaleTransaction.cpp
)
