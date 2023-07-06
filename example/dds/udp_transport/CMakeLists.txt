cmake_minimum_required (VERSION 3.10)

# 项目名称
project(test_dds_udp)

if(NOT fastrtps_FOUND)
    find_package(fastrtps REQUIRED)
endif()

# 检查当前编译器是否支持c++11
include(CheckCXXCompilerFlag)
if(CMAKE_COMPILER_IS_GNUCXX)
	check_cxx_compiler_flag(--std=c++11 SUPPORTS_CXX11)
	if(SUPPORTS_CXX11)
        add_compile_options(--std=c++11)
    else()
        message(FATAL_ERROR "Compiler doesn't support C++11")
    endif()
endif()

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(${PROJECT_NAME} ${DIR_SRCS})

# 添加链接库
target_link_libraries(${PROJECT_NAME} fastrtps)
