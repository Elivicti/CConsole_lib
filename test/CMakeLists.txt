# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.5)

# 项目信息
project (CConsole_Lib_Test)


# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

add_compile_options(-std=c11)

add_executable(test ${DIR_SRCS})
target_link_libraries(test CConsole)

add_custom_command(
	TARGET test PRE_BUILD
	COMMAND cmake -E copy_directory
	${CMAKE_SOURCE_DIR}/test/res/ ${CMAKE_SOURCE_DIR}/build/test/res)