cmake_minimum_required(VERSION 3.13)
project(Lab5_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab5_1 Main.cpp src/Customer.cpp include/Customer.h src/Shop.cpp include/Shop.h src/Product.cpp include/Product.h)