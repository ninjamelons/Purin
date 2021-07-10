cmake_minimum_required(VERSION 3.0.0)
project(Purin VERSION 0.1.0)

include(CTest)
enable_testing()

# Set build directories for executables and libraries
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(
  /home/filip/Repos/bullet3/src/
  /usr/include/
)

find_library(LinearMath NAMES LinearMath PATHS
    /home/filip/Repos/bullet3/build_cmake/src/LinearMath/)

add_library(LinearMath SHARED IMPORTED)
set_target_properties(LinearMath PROPERTIES IMPORTED_LOCATION ${LinearMath})


find_library(BulletCollision NAMES BulletCollision PATHS
    /home/filip/Repos/bullet3/build_cmake/src/BulletCollision/)

add_library(BulletCollision SHARED IMPORTED)
set_target_properties(BulletCollision PROPERTIES IMPORTED_LOCATION ${BulletCollision})


find_library(BulletDynamics NAMES BulletDynamics PATHS
    /home/filip/Repos/bullet3/build_cmake/src/BulletDynamics/)

add_library(BulletDynamics SHARED IMPORTED)
set_target_properties(BulletDynamics PROPERTIES IMPORTED_LOCATION ${BulletDynamics})


add_library(glad ${PROJECT_SOURCE_DIR}/lib/glad.c)


link_directories(/usr/lib ./lib)
add_executable(main src/main.cpp src/utils/shader.cpp)
target_link_libraries(main glfw glad LinearMath BulletCollision BulletDynamics ${CMAKE_DL_LIBS})

add_custom_target(
  compile_resources ALL
  DEPENDS main
)
add_custom_command(
    TARGET compile_resources PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/shaders $<TARGET_FILE_DIR:main>/shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/resources $<TARGET_FILE_DIR:main>/resources
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})

set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)