cmake_minimum_required(VERSION 3.6)
project(HW4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        hw.cpp)

add_executable(HW4 ${SOURCE_FILES})
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLM REQUIRED)

link_directories(/usr/local/lib)
target_link_libraries(HW4 libSOIL.a ${GLUT_LIBRARY} ${OPENGL_LIBRARY})
