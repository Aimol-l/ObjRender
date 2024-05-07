cmake_minimum_required(VERSION 3.20)
   
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20) # 设置为C++ 20标准
set(CMAKE_CXX_STANDARD_REQUIRED ON) #强制C++20
set(CMAKE_CXX_EXTENSIONS OFF)
set(THIS_PROJECT_NAME "main")
# 获取 CMakeLists.txt 文件所在目录的绝对路径
get_filename_component(PROJECT_DIR ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)
# 设置可执行文件的输出目录为 lib 目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_DIR}/bin)

set(CMAKE_BUILD_PARALLEL_LEVEL 16) 

project(
    ${THIS_PROJECT_NAME}        #项目名称
    LANGUAGES C CXX      #编程语言
    DESCRIPTION "obj加载库"
)

file(GLOB SRC_FILES
    CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/include/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_subdirectory(3rdpart)


include_directories(${PROJECT_DIR}/include)

add_executable(${THIS_PROJECT_NAME}  ${SRC_FILES})

target_link_libraries(${THIS_PROJECT_NAME} PUBLIC glad)
target_link_libraries(${THIS_PROJECT_NAME} PUBLIC glfw)
target_link_libraries(${THIS_PROJECT_NAME} PUBLIC spdlog)
target_link_libraries(${THIS_PROJECT_NAME} PUBLIC glm)
target_link_libraries(${THIS_PROJECT_NAME} PUBLIC assimp)
target_link_libraries(${THIS_PROJECT_NAME} PUBLIC imgui)

target_include_directories(glad INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/3rdpart/glad/include)
target_include_directories(glfw INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/3rdpart/glfw/include)
target_include_directories(spdlog INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/3rdpart/spdlog/include)
target_include_directories(glm INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/3rdpart/glm)
target_include_directories(imgui INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/3rdpart/imgui)