# POS 机模拟程序

## 1. 概述

模拟POS机，基于C++开发，采用C++标准库，使用CMake构建工具。该项目旨在通过C++语言实现一个功能全面的POS机模拟系统，利用C++标准库中的数据结构和算法来优化性能和代码可维护性。CMake作为构建工具，能够简化项目的构建过程，支持跨平台编译，确保代码在不同操作系统上的兼容性。

## 2. 功能介绍

POS 机模拟程序采用模块化设计，主要模块包括：

- **库存管理模块**：负责管理产品库存。
- **销售交易模块**：负责处理用户购买操作。
- **用户界面模块**：提供用户和管理端的交互界面。

## 3. 程序特点

- **模块化设计**：便于维护和扩展。
- **易于使用**：用户界面友好。
- **高效**：快速处理交易。

## 4. 应用场景

- 超市
- 小型零售店
- 餐饮业

## 5. 特点亮点

- **实时库存更新**：每次销售后自动更新库存。
- **用户友好的界面**：简洁明了的操作界面。
- **详细的销售记录**：便于追踪销售情况。

## 5. 运行

1. **克隆仓库**

``` bash
  git clone git@github.com:Miraitowa-zcx/pos-simulator.git
  
  cd pos-simulator
```

2. **构建项目**

``` bash
mkdir build 
cd build 
cmake .. 
make
```

3. **运行程序**

``` bash
./pos-simulator
```

## 6. 框架结构树

``` tree
pos-simulator
 ├── cmake-build-debug    Cmake 生成文件
 ├── cmake-build-release    Cmake 生成文件
 ├── data   数据文件
 ├── src    源代码
 │   ├── class    实现模块
 │   │   ├── Inventory.cpp    库存类
 │   │   ├── Product.cpp    产品类
 │   │   └── SaleTransaction.cpp    销售交易类
 │   ├── function   函数模块
 │   │   ├── MainMenu.cpp   主菜单函数
 │   │   ├── ManagerMenu.cpp    管理菜单函数
 │   │   └── VendingMachineMenu.cpp   销售交易菜单函数
 │   ├── include    声明模块
 │   │   ├── class    类声明模块
 │   │   │   ├── Inventory.hpp    库存类声明
 │   │   │   ├── Product.hpp    产品类声明
 │   │   │   └── SaleTransaction.hpp    销售交易类声明
 │   │   └── function   函数声明模块
 │   │        └── Menu.hpp    菜单函数声明
 │   └── Main.cpp   主函数
 ├── test   测试模块
 ├── CMakeLists.txt   CMake 配置文件
 ├── .clang-format   Clang 格式化配置文件
 ├── .editorconfig   编辑器配置文件
 ├── .gitignore   Git 忽略文件
 ├── LICENSE    开源协议
 ├── README.md    项目介绍
 └── symbol  象征
```

## 7. 技术栈

* C++
* CMake
* Git
* Markdown
* CLion

## 8. 贡献

代码贡献者：[Miraitowa_zcx](https://github.com/Miraitowa-zcx)

## 9. 版权声明

* Copyright (c) 2024 Leyramu. All rights reserved.
* This project (Lersosa), including its source code, documentation, and any associated materials, is
  the intellectual property of Leyramu. No part of this software may be reproduced, distributed, or transmitted in any
  form or by any means, including photocopying, recording, or other electronic or mechanical methods, without the prior
  written permission of the copyright owner, Miraitowa_zcx, except in the case of brief quotations embodied in critical
  reviews and certain other noncommercial uses permitted by copyright law.
* For inquiries related to licensing or usage outside the scope of this notice, please contact the copyright holder at
  2038322151@qq.com.
* The author disclaims all warranties, express or implied, including but not limited to the warranties of
  merchantability and fitness for a particular purpose. Under no circumstances shall the author be liable for any
  special, incidental, indirect, or consequential damages arising from the use of this software.
* By using this project, users acknowledge and agree to abide by these terms and conditions.
