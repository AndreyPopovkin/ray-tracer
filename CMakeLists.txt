cmake_minimum_required(VERSION 3.5)
project(RayTracer)

#set(CMAKE_C_COMPILER "C:\Program Files\mingw-w64\x86_64-6.3.0-posix-seh-rt_v5-rev1\mingw64\bin\gcc.exe")

#set(CMAKE_CXX_COMPILER "C:\Program Files\mingw-w64\x86_64-6.3.0-posix-seh-rt_v5-rev1\mingw64\bin\g++.exe")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall\
 -Wextra -pedantic -std=c++11 -O2 -Wshadow -Wformat=2 -Wfloat-equal\
 -Wconversion -Wlogical-op -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG\
 -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address\
 -fsanitize=undefined -fno-sanitize-recover -fstack-protector -DGC_LOG")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")


set(SOURCE_FILES main.cpp point.cpp vector.cpp sphere.cpp 
    drawer.cpp scene.cpp ray.cpp rayTracer.cpp star.cpp tetragon.cpp
    triangle.cpp polygon.cpp KDtree.cpp KDtreeVertex.cpp
    )

add_executable(trace ${SOURCE_FILES})

target_link_libraries(trace SDL2main SDL2)