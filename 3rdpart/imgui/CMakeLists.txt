project(imgui)
set(THIS_PROJECT_NAME "imgui")

# # 使用GLOB收集所有源文件
# file(GLOB SRC_FILES
#     CONFIGURE_DEPENDS   
#     "*.cpp"
#     "*.h"
# )

add_library(${THIS_PROJECT_NAME} STATIC ${SRC_FILES})

target_sources(${THIS_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_demo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_draw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_widgets.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_tables.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/backends/imgui_impl_glfw.h
    ${CMAKE_CURRENT_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/backends/imgui_impl_opengl3.h
    ${CMAKE_CURRENT_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

# target_include_directories(${THIS_PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/backends)


