cmake_minimum_required(VERSION 3.15)
project(sdl_hello C)

set(CMAKE_C_STANDARD 11)

LINK_DIRECTORIES(/Users/flogan/.brew/lib)
LINK_DIRECTORIES(./ft_printf/)
include_directories(/Users/flogan/.brew/include/SDL2)
include_directories(/Users/flogan/.brew/include/SDL2_image)
add_executable(sdl_hello
        visualisation/main_visual.c parser.c valid.c freez.c list_methods.c djkstra.c visualisation/visual_header.h visualisation/list_method_vis.c)


find_package(OpenGL REQUIRED)
target_link_libraries(sdl_hello ${OPENGL_LIBRARIES} SDL2 SDL2_image ftprintf)