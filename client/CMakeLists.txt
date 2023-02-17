include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/srcs CLIENT-SRCS)
aux_source_directory(${CMAKE_SOURCE_DIR}/utils UTILS)

add_executable("${CMAKE_PROJECT_NAME}-client" client.cpp ${CLIENT-SRCS} ${UTILS})