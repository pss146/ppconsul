cmake_minimum_required(VERSION 3.5)
project(test_package CXX)

set (CMAKE_CXX_STANDARD 11)
#set(CMAKE_VERBOSE_MAKEFILE TRUE)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME} test_package.cpp)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${CONAN_DEFINES})


