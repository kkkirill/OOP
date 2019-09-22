cmake_minimum_required(VERSION 3.13)
project(Lab4_1)

set(CMAKE_CXX_STANDARD 17)
include_directories(.)

add_executable(Lab4_1 main.cpp
        include/Person.h
        src/Person.cpp src/Bank.cpp include/Bank.h src/BankAccount.cpp include/BankAccount.h)
