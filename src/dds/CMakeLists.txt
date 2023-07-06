cmake_minimum_required (VERSION 3.10)

project(fastdds_pkg)

if(NOT fastrtps_FOUND)
    find_package(fastrtps REQUIRED)
endif()

include(CheckCXXCompilerFlag)
if(CMAKE_COMPILER_IS_GNUCXX)
	check_cxx_compiler_flag(--std=c++11 SUPPORTS_CXX11)
	if(SUPPORTS_CXX11)
        add_compile_options(--std=c++11)
    else()
        message(FATAL_ERROR "Compiler doesn't support C++11")
    endif()
endif()

aux_source_directory(. DIR_SRCS)
add_library(${PROJECT_NAME} ${DIR_SRCS})

target_link_libraries(${PROJECT_NAME} fastrtps)
