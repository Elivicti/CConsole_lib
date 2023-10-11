# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.5)

# 项目信息
project (CConsole_Lib)


# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

set(C_STANDARD 11)

# 指定生成目标
add_library(CConsole STATIC ${DIR_SRCS})

set_target_properties(CConsole PROPERTIES LIBRARY_OUTPUT_NAME "CConsole.lib")
set_target_properties(CConsole PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)