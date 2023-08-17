project(test_publisher)

include(CheckCXXCompilerFlag)
if(CMAKE_COMPILER_IS_GNUCXX)
	check_cxx_compiler_flag(--std=c++11 SUPPORTS_CXX11)
	if(SUPPORTS_CXX11)
        add_compile_options(--std=c++11)
    else()
        message(FATAL_ERROR "Compiler doesn't support C++11")
    endif()
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/test/test_pubsub/idls)

aux_source_directory(. DIR_SRCS)
add_executable(${PROJECT_NAME} ${DIR_SRCS})

target_link_libraries(${PROJECT_NAME} idls)
target_link_libraries(${PROJECT_NAME} fastddscpp)
target_link_libraries(${PROJECT_NAME} glog)