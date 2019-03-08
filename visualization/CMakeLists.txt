project(visualization)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -O3 -pthread")

add_executable(visualization window.cpp corewar.cpp visualization.cpp text.cpp)

target_link_libraries(visualization /Users/kpshenyc/projects/corewar/visualization/libs/libSDL2-2.0.0.dylib /Users/kpshenyc/projects/corewar/visualization/libs/libSDL2_ttf-2.0.0.dylib /Users/kpshenyc/projects/corewar/visualization/libs/libSDL2_image-2.0.0.dylib)