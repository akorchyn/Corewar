project(visualization)

set(CMAKE_CXX_STANDARD 17)

add_executable(visualization window.cpp corewar.cpp visualization.cpp )

target_link_libraries(visualization /Users/kpshenyc/projects/corewar/visualization/libs/libSDL2-2.0.0.dylib /Users/kpshenyc/projects/corewar/visualization/libs/libSDL2_ttf-2.0.0.dylib)