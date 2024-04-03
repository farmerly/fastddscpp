cmake_minimum_required (VERSION 3.0)

project(simplest-fast-dds)

# 设定编译选项
add_compile_options(-g)
add_compile_options(-std=c++11)

# 设置输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

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

find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)

# add_subdirectory(example)
add_subdirectory(src)
# add_subdirectory(test)
