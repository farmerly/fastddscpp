project(utils)

aux_source_directory(. DIR_LIB_SRCS)

add_library (${PROJECT_NAME} ${DIR_LIB_SRCS})
 