cmake_minimum_required (VERSION 2.6)
project (LearnOpenGL)

include_directories(/usr/local/include ./include)
link_directories(/usr/local/lib)

add_executable(learnOpenGL main.cpp src/glad.c)
target_link_libraries(learnOpenGL glfw)
