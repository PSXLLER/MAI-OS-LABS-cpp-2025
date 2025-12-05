cmake_minimum_required(VERSION 3.10)

project(MultiConv CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_executable(conv
    src/main.cpp
    src/matrix.cpp
    src/convolution.cpp
)

if(WIN32)
    target_sources(conv PRIVATE src/os_wrapper_win.cpp)
    target_link_libraries(conv PRIVATE ws2_32)
else()
    target_sources(conv PRIVATE src/os_wrapper_linux.cpp)
    target_link_libraries(conv PRIVATE pthread)
endif()

add_custom_target(run
    COMMAND conv
        ${CMAKE_SOURCE_DIR}/example/input.txt
        ${CMAKE_SOURCE_DIR}/example/output.txt
        ${CMAKE_SOURCE_DIR}/example/kernel.txt
        1 4
    DEPENDS conv
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
