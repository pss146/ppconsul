#  Copyright (c) 2014-2017 Andrey Upadyshev <oliora@gmail.com>
#
#  Use, modification and distribution are subject to the
#  Boost Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.5)

project(Ppconsul LANGUAGES CXX VERSION 0.1)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
SET(BOOST_ROOT "${CONAN_BOOST_ROOT}")
SET(CURL_ROOT "${CONAN_CURL_ROOT}")
SET(CATCH2_ROOT "${CONAN_CATCH2_ROOT}")

option(BUILD_SHARED_LIBS "Build Ppconsul as shared library" OFF)
option(BUILD_TESTS "Build Ppconsul tests" ON)

include(GNUInstallDirs)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

# Build position independent code.
# https://eli.thegreenplace.net/2011/11/03/position-independent-code-pic-in-shared-libraries/
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(BOOST_MIN_VERSION 1.66)

if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
#    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC")
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
#    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC -ftemplate-depth=256")
elseif (MSVC)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")

    # Turn off MS specific warnings that shown for standard compatible code (mostly for Boost)
#    add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS)

    # Build for Windows Vista / Windows Server 2008
#    add_definitions(-D_WIN32_WINNT=0x0600)

    set(Boost_USE_STATIC_LIBS ON)
    #set(Boost_USE_STATIC_RUNTIME OFF)
endif()

if (BUILD_TESTS)
    enable_testing()
endif()

find_package(Boost ${BOOST_MIN_VERSION} REQUIRED)
find_package(CURL REQUIRED)
find_package(Catch2 REQUIRED)

set(HEADERS_DIR "${PROJECT_SOURCE_DIR}/include/ppconsul")

add_subdirectory(ext/json11)
add_subdirectory(src)
if (BUILD_TESTS)
    add_subdirectory(tests)
endif()

install(
    DIRECTORY "${HEADERS_DIR}"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install(EXPORT ${CMAKE_PROJECT_NAME} DESTINATION cmake FILE ppconsulConfig.cmake)
export(EXPORT ${CMAKE_PROJECT_NAME} FILE ppconsulConfig.cmake)

# Generate and install pkg-config file
if (NOT WIN32 OR CYGWIN)
    if (NOT BUILD_SHARED_LIBS)
        set(ppconsul_libs "-lppconsul -ljson11")
    else()
        set(ppconsul_libs "-lppconsul")
    endif()

    configure_file(ppconsul.pc.in ppconsul.pc @ONLY)

    install(
        FILES "${CMAKE_CURRENT_BINARY_DIR}/ppconsul.pc"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
    )
endif()

