project(imgui)
set(THIS_PROJECT_NAME "imgui")

# 使用GLOB收集所有源文件
file(GLOB SOURCE_FILES
    "*.cpp"
    "*.h"
)

add_library(${THIS_PROJECT_NAME} STATIC ${SOURCE_FILES})

target_include_directories(${THIS_PROJECT_NAME} PUBLIC backends)


