cmake_minimum_required(VERSION 3.8)
project(dz2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp BigDecimal.cpp BigDecimal.h TreeNode.cpp TreeNode.h RSearchTree.cpp RSearchTree.h)
add_executable(dz2 ${SOURCE_FILES})