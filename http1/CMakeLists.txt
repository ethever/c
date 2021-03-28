cmake_minimum_required(VERSION 3.13)

# 指定输出文件位置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../output/)
project(http1)

add_executable(server src/server.c)
add_executable(client src/client.c)


