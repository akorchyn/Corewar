project(visualization)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_executable(visualization window.cpp corewar.cpp visualization.cpp text.cpp)

target_link_libraries(visualization /Users/kpshenyc/projects/corewar/visualization/libs/libSDL2-2.0.0.dylib /Users/kpshenyc/projects/corewar/visualization/libs/libSDL2_ttf-2.0.0.dylib)