project(glad)
set(THIS_PROJECT_NAME "glad")

add_library(${THIS_PROJECT_NAME} OBJECT)

target_sources(${THIS_PROJECT_NAME} PRIVATE src/glad.c include/glad/glad.h include/KHR/khrplatform.h)

target_include_directories(${THIS_PROJECT_NAME} PUBLIC include)
