project(DDSHandler)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/test/test_pubsub/ddsidls)

aux_source_directory(. SRC_FILES)
add_library(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} idls)
target_link_libraries(${PROJECT_NAME} fastddscpp)