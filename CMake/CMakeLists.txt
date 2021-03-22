cmake_minimum_required(VERSION 3.10)

# 设置项目名字和版本号
project(Tutorial VERSION 1.0)

# 配置头文件 将版本号传递给源代码
configure_file(TutorialConfig.h.in TutorialConfig.h)

# 上面这个配置文件会被写入二进制树 我们必须将那个目录添加到查找包含文件的路径中
target_include_directories(Tutorial PUBLIC "${PROJECT_BINARY_DIR}")


# 添加可执行文件
add_executable(Tutorial tutorial.cxx)

