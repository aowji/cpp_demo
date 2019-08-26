cmake_minimum_required(VERSION 3.1)

find_package(PythonLibs 3 REQUIRED)

include_directories(${PYTHON_INCLUDE_DIRS})

add_executable(call_class call_class.c)
target_link_libraries(call_class ${PYTHON_LIBRARY})

add_executable(call_function call_function.c)
target_link_libraries(call_function ${PYTHON_LIBRARY})

add_executable(call_thread_2 call_thread_2.c)
target_link_libraries(call_thread_2 ${PYTHON_LIBRARY})

add_executable(call_thread call_thread.c)
target_link_libraries(call_thread ${PYTHON_LIBRARY})
