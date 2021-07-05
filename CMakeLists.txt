cmake_minimum_required(VERSION 3.0.0)
project(Purin VERSION 0.1.0)

include(CTest)
enable_testing()

# Set build directories for executables and libraries
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(glad ${PROJECT_SOURCE_DIR}/lib/glad.c)

link_directories(/usr/lib ./lib)
add_executable(main src/main.cpp src/utils/shader.cpp)
target_link_libraries(main glfw glad ${CMAKE_DL_LIBS})

add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory              
        ${CMAKE_SOURCE_DIR}/src/shaders $<TARGET_FILE_DIR:main>/shaders
    COMMENT "Copying shaders" VERBATIM
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})

set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
