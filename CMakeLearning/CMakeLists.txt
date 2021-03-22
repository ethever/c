cmake_minimum_required (VERSION 2.8)
# 添加c++11标准支持
set(CMAKE_CXX_FLAGS "-std=c++11")

# 声明一个cmake工程
project (Main)
#打印相关消息
message(STATUS "Project:SERVER")

# 指定生成目标
add_executable(main main.c)
