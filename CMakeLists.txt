cmake_minimum_required (VERSION 2.6)
project (LearnOpenGL)

include_directories(/usr/local/include ./include)
link_directories(/usr/local/lib)

add_executable(learnOpenGL main.cpp src/glad.c src/shader.cpp src/stb_image.cpp src/texture.cpp src/camera.cpp src/mesh.cpp src/model.cpp)
target_link_libraries(learnOpenGL glfw)
