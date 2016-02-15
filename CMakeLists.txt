cmake_minimum_required(VERSION 3.3)
project(opengl_tutorials)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SB7_DIR C:/Users/swart/apps/sb7)

find_package(OpenGL)
link_directories(${SB7_DIR}/lib)
include_directories(${SB7_DIR}/include)
include_directories(${SB7_DIR}/extern/glfw-3.0.4/include)
set(COMMON_LIBS sb7 optimized glfw3 debug glfw3_d ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES})
add_library(sb7
    ${SB7_DIR}/src/sb7/sb7.cpp
    ${SB7_DIR}/src/sb7/sb7color.cpp
    ${SB7_DIR}/src/sb7/sb7ktx.cpp
    ${SB7_DIR}/src/sb7/sb7object.cpp
    ${SB7_DIR}/src/sb7/sb7shader.cpp
    ${SB7_DIR}/src/sb7/sb7textoverlay.cpp
    ${SB7_DIR}/src/sb7/gl3w.c
)

set(SOURCE_FILES chapter_1/color.cpp)
add_executable(color ${SOURCE_FILES})
target_link_libraries(color ${COMMON_LIBS})

set(SOURCE_FILES  chapter_1/dot.cpp)
add_executable(dot ${SOURCE_FILES})
target_link_libraries(dot ${COMMON_LIBS})
