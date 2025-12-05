cmake_minimum_required(VERSION 3.10)
project(Lab4_Var10 CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)

add_library(func1_derivative_v1 SHARED src/func1_derivative_v1.cpp)
add_library(func1_derivative_v2 SHARED src/func1_derivative_v2.cpp)
add_library(func2_gcf_v1       SHARED src/func2_gcf_v1.cpp)
add_library(func2_gcf_v2       SHARED src/func2_gcf_v2.cpp)

add_executable(main_link src/main_link.cpp)
target_link_libraries(main_link PRIVATE func1_derivative_v1 func2_gcf_v1)

add_executable(main_runtime
    src/main_runtime.cpp
    src/os_wrapper.cpp
)

if(UNIX AND NOT APPLE)
    target_link_libraries(main_runtime PRIVATE dl)
endif()
