cmake_minimum_required(VERSION 3.0.0)
project(Purin VERSION 0.1.0)

include(CTest)
enable_testing()

# Set build directories for executables and libraries
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(
  /usr/include/
  /usr/include/bullet/
)

add_library(glad ${PROJECT_SOURCE_DIR}/lib/glad.c)
add_library(imgui_backend
  ${PROJECT_SOURCE_DIR}/lib/imgui_impl_opengl3.cpp
  ${PROJECT_SOURCE_DIR}/lib/imgui_impl_glfw.cpp
)

add_library(purinCore 
  src/core/Scene.cpp
  src/core/Quaternion.cpp
  src/core/GameObject.cpp
  src/core/Transform.cpp
  src/core/Renderer.cpp
  src/core/Mesh.cpp
)

link_directories(/usr/lib ./lib)
add_executable(main src/main.cpp src/utils/shader.cpp)
target_link_libraries(main
  glfw glad imgui imgui_backend
  LinearMath BulletCollision BulletDynamics
  purinCore
  ${CMAKE_DL_LIBS}
)

add_custom_target(
  compile_resources ALL
  DEPENDS main
)
add_custom_command(
    TARGET compile_resources PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/resources $<TARGET_FILE_DIR:main>/resources
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})

set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)