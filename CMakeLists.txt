cmake_minimum_required(VERSION 3.16)

project(CP4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


find_package(yaml-cpp REQUIRED)
if (yaml-cpp_FOUND)
    message(STATUS "----> found yaml-cpp")
endif ()

find_package(PythonInterp REQUIRED)


add_subdirectory(tinyMeta)
add_subdirectory(CP4)
