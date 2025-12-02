cmake_minimum_required(VERSION 3.10)

project(lab3_var8)

include_directories(include)

set(SOURCES_PARENT
    src/parent.cpp
)

set(SOURCES_CHILD
    src/child.cpp
)

if (WIN32)
    set(OS_WRAPPER src/os_wrapper_win.cpp)
else()
    set(OS_WRAPPER src/os_wrapper_linux.cpp)
endif()

add_executable(parent ${SOURCES_PARENT} ${OS_WRAPPER})
add_executable(child  ${SOURCES_CHILD}  ${OS_WRAPPER})
