cmake_minimum_required(VERSION 3.1)

project(test)

set(CXX_STANDARD_REQUIRED 11)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_ttf_INCLUDE_DIR})
add_executable(test main.cpp netspeed.h netspeed.cpp ui.h ui.cpp)
target_link_libraries(test ${SDL2_LIBS} ${SDL2_ttf_LIBS} Iphlpapi)