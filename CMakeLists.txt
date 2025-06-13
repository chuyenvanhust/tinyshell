cmake_minimum_required(VERSION 3.10.2)

project(IT3070 VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")

add_executable(IT3070 main.cpp)
target_link_libraries(IT3070 PRIVATE iphlpapi)
add_definitions(-DNOMINMAX)

install(TARGETS IT3070 RUNTIME DESTINATION .)

add_subdirectory(Process)