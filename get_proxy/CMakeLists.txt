cmake_minimum_required(VERSION 3.1)

project(get_proxy)

find_package(PythonLibs REQUIRED)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS python37)

add_executable(get_proxy main.cpp)
target_link_libraries(get_proxy Winhttp)


include_directories(${PYTHON_INCLUDE_DIRS} ${Boost_INCLUDE_DIR})
add_library(getproxy SHARED getproxy_wrapper.cpp)
target_link_libraries(getproxy ${PYTHON_LIBRARIES} ${Boost_LIBRARIES})

if(CMAKE_GENERATOR MATCHES "^Visual Studio")
	message(using visual studio)
endif()

