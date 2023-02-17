include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/srcs SERVER-SRCS)
aux_source_directory(${UTILS_DIR_PATH} UTILS)

add_executable("${CMAKE_PROJECT_NAME}-server" main.cpp ${SERVER-SRCS} ${UTILS})