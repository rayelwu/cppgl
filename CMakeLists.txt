#cmake_minimum_required(VERSION 3.0.0)
cmake_minimum_required(VERSION 3.27)
project(CppGL VERSION 0.1.0)

# 使用 C++ 17 标准
#set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17")

# 设置代码文件
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src/ )

# 添加头文件
set(HEADER_DIR 
    ${PROJECT_SOURCE_DIR}/include/ 
    ${PROJECT_SOURCE_DIR}/src/ 
    ${PROJECT_SOURCE_DIR}/src/loader 
    ${PROJECT_SOURCE_DIR}/src/model
    ${PROJECT_SOURCE_DIR}/src/renderer
)

set(SOURCES 
    ${SRC_DIR}glad.c 
    ${SRC_DIR}/shader/Shader.cpp
    ${SRC_DIR}/renderer/Renderer.cpp
    ${SRC_DIR}/model/RawModel.cpp
    ${SRC_DIR}/loader/Loader.cpp
    ${SRC_DIR}/main.cpp
)

set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib/)
include_directories(${HEADER_DIR} ${LIB_DIR})

# 添加目标链接
#set(GLFW_LINK ${LIB_DIR}libglfw3.a)
#link_libraries(${GLFW_LINK})
link_directories(${LIB_DIR})
add_executable(CppGL ${SOURCES})

# 链接系统的 OpenGL 框架
if (APPLE)
    target_link_libraries(CppGL "-framework OpenGL")
endif()

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
target_link_libraries(CppGL glfw3)