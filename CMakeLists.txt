cmake_minimum_required(VERSION 3.3)
project(opengl_tutorials)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SB7_DIR C:/Users/swart/apps/sb7)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

find_package(OpenGL)
link_directories(${SB7_DIR}/lib)
include_directories(${CMAKE_SOURCE_DIR})
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

file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/)
set(EXERCISES
    chapter_02_color
    chapter_02_dot
    chapter_02_triangle
    chapter_03_animated_triangle
    chapter_03_color_triangle
    chapter_03_tessalated_triangle
)
foreach(EXERCISE ${EXERCISES})
    message(WARNING "building exercise" ${EXERCISE})
    set(SOURCE_FILES src/${EXERCISE}.cpp opengl_tutorials.h debug.cpp)
    add_executable(${EXERCISE} ${SOURCE_FILES})
    target_link_libraries(${EXERCISE} ${COMMON_LIBS})
endforeach(EXERCISE)

